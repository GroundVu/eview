
#include <iostream>
#include <QApplication>
#include <QSettings>

#include "eview.h"

#include "Scene.h"
#include "SceneQuickView.h"
#include "Basemap.h"
#include "ArcGISTiledElevationSource.h"
#include "ArcGISSceneLayer.h"
#include "Point.h"
#include "Viewpoint.h"
#include "Camera.h"

#include "dialog.h"

using namespace Esri::ArcGISRuntime;

DisplaySceneLayer *DisplaySceneLayer ::sceneLayer = NULL;

DisplaySceneLayer::DisplaySceneLayer(QQuickItem* parent) :
    QQuickItem(parent),
    m_scene(nullptr),
    m_sceneView(nullptr),
    m_sceneLayer(nullptr)
{
    connect(this, SIGNAL(showDialogSignal()), this, SLOT(showDialog()));
    DisplaySceneLayer::sceneLayer = this;
    settings_filename_ = QApplication::applicationDirPath() + "/settings.ini";
}

DisplaySceneLayer::~DisplaySceneLayer()
{
    writeStateSettings();
}

void DisplaySceneLayer::componentComplete()
{
    QQuickItem::componentComplete();

    int buttons_num = 6;
    for (int i=0; i<buttons_num; i++){
        SceneLayer *layer = new SceneLayer();
        layer->name = "layer "+QString::number(i);
        layers.push_back(layer);
    }

    for (int i=0; i<layers.size(); i++){
        QString name = "layer_btn_"+QString::number(i+1);
        QObject *btn = findChild<QObject*>(name);
        btn->setProperty("text", "");
    }

    // find QML SceneView component
    m_sceneView = findChild<SceneQuickView*>("sceneView");

    // create a new scene instance
    Basemap* basemap = Basemap::topographic(this);
    m_scene = new Scene(basemap, this);

    // create a new elevation source and add to scene
    elevationSource = new ArcGISTiledElevationSource(QUrl("http://elevation3d.arcgis.com/arcgis/rest/services/WorldElevation3D/Terrain3D/ImageServer"), this);

//    // create a camera and set the initial viewpoint
//    Point pt(-4.49779155626782, 48.38282454039932, 62.013264927081764, SpatialReference(4326));
//    Camera camera(pt, 41.64729875588979, 71.2017391571523, 2.194677223e-314);
//    Viewpoint initViewpoint(pt, camera);
//    //Viewpoint initViewpoint(env, camera);
//    m_scene->setInitialViewpoint(initViewpoint);


    // set scene on the scene view
    m_sceneView->setArcGISScene(m_scene);

    readStateSettings();
}


void DisplaySceneLayer::readStateSettings()
{
    QSettings qsettings(settings_filename_, QSettings::IniFormat);

    qsettings.beginGroup( "layers" );

    for (int i=0; i<layers.size(); i++){
        QString layer_name = "layer_"+QString::number(i);

        layers[i]->url = qsettings.value(layer_name+"_url").toString();
        layers[i]->name = qsettings.value(layer_name+"_name").toString();

        bool selected = qsettings.value(layer_name+"_selected").toBool();
        layers[i]->selected = selected;
    }
    qsettings.endGroup();

    loadLayers();

    qsettings.beginGroup( "view" );
    QString viewpoint_json = qsettings.value("viewpoint").toString();

    if (viewpoint_json != ""){
        Viewpoint vp  = Viewpoint::fromJson(viewpoint_json);
        if (!vp.isEmpty()){
            //m_scene->setInitialViewpoint(vp);
           m_sceneView->setViewpointAndWait(vp);
        }
    }

    setCurrentBasemap(qsettings.value("basemap").toInt());
    setElevationStatus(qsettings.value("elevation").toBool());

    qsettings.endGroup();

}

void DisplaySceneLayer::writeStateSettings()
{
    QSettings qsettings(settings_filename_, QSettings::IniFormat);
    qsettings.beginGroup( "layers" );

    for (int i=0; i<layers.size(); i++){
        QString layer_name = "layer_"+QString::number(i);
        qsettings.setValue(layer_name+"_name", layers[i]->name );
        qsettings.setValue(layer_name+"_url", layers[i]->url );

        QString btn_name = "layer_btn_"+QString::number(i+1);
        QObject *btn =  findChild<QObject*>(btn_name);
        bool checked = false;
        if (btn){
            checked = btn->property("checked").toBool();
        }
        qsettings.setValue(layer_name+"_selected", checked);
    }

    qsettings.endGroup();

    qsettings.beginGroup( "view" );
    Viewpoint vp = m_scene->initialViewpoint();
    vp = m_sceneView->currentViewpoint(Esri::ArcGISRuntime::ViewpointType::CenterAndScale);

    QString viewpoint_json = vp.toJson();
    qsettings.setValue("viewpoint", viewpoint_json);

    qsettings.setValue("basemap", getCurrentBasemap());
    qsettings.setValue("elevation", getElevationStatus());
    qsettings.endGroup();
}


void DisplaySceneLayer::loadLayers()
{
    for (int i=0; i<layers.size(); i++){
        SceneLayer *sl = layers[i];

        QString btn_name = "layer_btn_"+QString::number(i+1);
        QObject *btn =  findChild<QObject*>(btn_name);
        if (!btn)
            continue;

        // Create and display new Layer
        if (sl->m_sceneLayer){
            m_scene->operationalLayers()->removeOne(sl->m_sceneLayer);
            delete sl->m_sceneLayer;
        }

        // http://scene.arcgis.com/arcgis/rest/services/Hosted/Buildings_Brest/SceneServer/layers/0
        // http://tiles.arcgis.com/tiles/GrCObcYo81O3Ymu8/arcgis/rest/services/North_Mine/SceneServer
        if (sl->url != ""){
            sl->m_sceneLayer = new ArcGISSceneLayer(QUrl(sl->url));
            m_scene->operationalLayers()->append(sl->m_sceneLayer);
        }


        btn->setProperty("text", sl->name);

        if (sl->m_sceneLayer){
            if (sl->selected){
                sl->m_sceneLayer->setVisible(true);
                btn->setProperty("checked", true);
            }else{
                sl->m_sceneLayer->setVisible(false);
                btn->setProperty("checked", false);
            }
        }else{
            btn->setProperty("checked", false);
        }

    }


}


bool DisplaySceneLayer::getElevationStatus()
{
    QObject *elv_button =  findChild<QObject*>("elv_button");
    if (!elv_button)
        return false;

    bool result = elv_button->property("checked").toBool();
    return result;
}

void DisplaySceneLayer::setElevationStatus(bool checked)
{
    QObject *elv_button =  findChild<QObject*>("elv_button");
    if (!elv_button)
        return;

    elv_button->setProperty("checked", checked);
}



void DisplaySceneLayer::elevationChanged(bool checked)
{
    if (m_scene->loadStatus() == LoadStatus::Loaded){

        if (checked)
            m_scene->baseSurface()->elevationSources()->append(elevationSource);
        else
            m_scene->baseSurface()->elevationSources()->removeOne(elevationSource);

    }
}


int DisplaySceneLayer::getCurrentBasemap()
{
    QObject *combo =  findChild<QObject*>("comboBoxBasemap");
    if (!combo)
        return -1;

    int baseMapId = combo->property("currentIndex").toInt();
    return baseMapId;
}


void DisplaySceneLayer::setCurrentBasemap(int baseMapId)
{
    QObject *combo =  findChild<QObject*>("comboBoxBasemap");
    if (!combo)
        return;

    combo->setProperty("currentIndex", baseMapId);
}


void DisplaySceneLayer::changeBasemap(QString basemap)
{
    if (m_scene->loadStatus() == LoadStatus::Loaded)
    {
        if (basemap == "Topographic")
            m_scene->setBasemap(Basemap::topographic(this));
        else if (basemap == "Streets")
            m_scene->setBasemap(Basemap::streets(this));
        else if (basemap == "Imagery")
            m_scene->setBasemap(Basemap::imagery(this));
        else if (basemap == "Oceans")
            m_scene->setBasemap(Basemap::oceans(this));
    }
}

void DisplaySceneLayer::showDialog()
{
    Dialog dialog;
    int result = dialog.exec();
    std::cout << "result " << result << std::endl;
}


void DisplaySceneLayer::loadLayer(QString name, bool checked)
{
    QObject *btn =  findChild<QObject*>(name);
    if (!btn)
        return;

    QStringList name_parts = name.split('_');
    int id = name_parts.last().toInt();

    SceneLayer *sl = layers[id-1];

    if (keyDown == 123 || sl->m_sceneLayer == NULL){
        keyDown = -1;
//        showDialog();

        Dialog dialog;
        dialog.setData(sl->url, sl->name);
        int result = dialog.exec();
        std::cout << "result " << result << std::endl;

        if (result == 1){
            sl->url = dialog.getURL();
            sl->name = dialog.getName();
        }else{
            if (!sl->m_sceneLayer)
                btn->setProperty("checked", false);
            return;
        }

        // Create and display new Layer
        if (sl->m_sceneLayer){
            m_scene->operationalLayers()->removeOne(sl->m_sceneLayer);
            delete sl->m_sceneLayer;
        }

        // http://scene.arcgis.com/arcgis/rest/services/Hosted/Buildings_Brest/SceneServer/layers/0
        // http://tiles.arcgis.com/tiles/GrCObcYo81O3Ymu8/arcgis/rest/services/North_Mine/SceneServer
        sl->m_sceneLayer = new ArcGISSceneLayer(QUrl(sl->url));
        m_scene->operationalLayers()->append(sl->m_sceneLayer);


        if (sl->name != "")
            btn->setProperty("text", sl->name);

        if (sl->m_sceneLayer)
            btn->setProperty("checked", true);
        else
            btn->setProperty("checked", false);

        return;
    }

    if (keyDown == Qt::Key_Z && sl->m_sceneLayer){
        btn->setProperty("checked", true);
        sl->m_sceneLayer->setVisible(true);
        Envelope env = sl->m_sceneLayer->fullExtent();
        Viewpoint vp(env);
        m_sceneView->setViewpointAndWait(vp);
        return;
    }


    btn->setProperty("text", sl->name);
    if (checked){
        sl->m_sceneLayer->setVisible(true);
    }else{
        sl->m_sceneLayer->setVisible(false);
    }

}


bool DisplaySceneLayer::eventFilter(QObject *target, QEvent *event)
{

        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            keyDown = keyEvent->key();

            if (keyEvent->modifiers().testFlag(Qt::ShiftModifier)){
                keyDown = 123;
                return true;
            }

            std::cout << "KeyPress " << keyDown << std::endl;
        }else
        if (event->type() == QEvent::KeyRelease) {
            std::cout << "keyReleaseEvent " << keyDown << std::endl;
            keyDown = -1;
        }

    return QQuickItem::eventFilter(target, event);
}
