#ifndef DISPLAYSCENELAYER_H
#define DISPLAYSCENELAYER_H

namespace Esri
{
    namespace ArcGISRuntime
    {
        class Scene;
        class SceneQuickView;
        class ArcGISSceneLayer;
        class ArcGISTiledElevationSource;
    }
}

#include <QQuickItem>

class DisplaySceneLayer;

class SceneLayer
{

public:
    SceneLayer(){
        url="";
        name="";
        m_sceneLayer = NULL;
        selected = false;
    }

    QString url;
    QString name;
    bool selected;
    Esri::ArcGISRuntime::ArcGISSceneLayer* m_sceneLayer;
};

class DisplaySceneLayer : public QQuickItem
{
    Q_OBJECT

public:
    DisplaySceneLayer(QQuickItem* parent = 0);
    ~DisplaySceneLayer();

    static DisplaySceneLayer *sceneLayer;

    void componentComplete() Q_DECL_OVERRIDE;

    Q_INVOKABLE void changeBasemap(QString basemap);
    Q_INVOKABLE void loadLayer(QString name, bool checked);
    Q_INVOKABLE void elevationChanged(bool checked);


    void readStateSettings();
    void writeStateSettings();
    void updateLayers();
    void loadLayers();
    int getCurrentBasemap();
    bool getElevationStatus();
    void setCurrentBasemap(int basemap);
    void setElevationStatus(bool checked);

    virtual bool eventFilter(QObject *target, QEvent *event);


private slots:
    void showDialog();

signals:
    void showDialogSignal();

private:
    QString settings_filename_;
    Esri::ArcGISRuntime::Scene* m_scene;
    Esri::ArcGISRuntime::SceneQuickView* m_sceneView;
    Esri::ArcGISRuntime::ArcGISSceneLayer* m_sceneLayer;
    Esri::ArcGISRuntime::ArcGISTiledElevationSource* elevationSource;
    std::vector<SceneLayer*> layers;
    int keyDown;
};

#endif // DISPLAYSCENELAYER_H

