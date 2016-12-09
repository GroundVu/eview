#include <QSettings>
#include <QGuiApplication>
#include <QApplication>
#include <QQuickView>
#include <QCommandLineParser>
#include <QDir>
#include <QQmlEngine>
#include <QSurfaceFormat>

#ifdef Q_OS_WIN
#include <Windows.h>
#endif

#include "SceneQuickView.h"
#include "eview.h"
#include "ArcGISRuntimeEnvironment.h"

using namespace Esri::ArcGISRuntime;

int main(int argc, char *argv[])
{
#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)
    // Linux requires 3.2 OpenGL Context
    // in order to instance 3D symbols
    QSurfaceFormat fmt = QSurfaceFormat::defaultFormat();
    fmt.setVersion(3, 2);
    QSurfaceFormat::setDefaultFormat(fmt);
#endif

    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);

#ifdef Q_OS_WIN
    // Force usage of OpenGL ES through ANGLE on Windows
    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
#endif

    // Register the map view for QML
    qmlRegisterType<SceneQuickView>("Esri.Samples", 1, 0, "SceneView");
    qmlRegisterType<DisplaySceneLayer>("Esri.Samples", 1, 0, "DisplaySceneLayerGUI");

    // Intialize application view
    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);

    // Add the import Path
    view.engine()->addImportPath(QDir(QCoreApplication::applicationDirPath()).filePath("qml"));

    // Set the source
    view.setSource(QUrl("qrc:/eview.qml"));

    view.setTitle("GroundVu Map Viewer ("+QString(VERSION)+")");
    view.show();
    view.installEventFilter(DisplaySceneLayer::sceneLayer);

    return app.exec();
}


