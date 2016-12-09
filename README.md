# eview
GUI application to load and display multiple sceen layers. 

![GitHub Logo](/screenshot.png)

# Usage 
There is possible to load up to 6 layers, each controlled by one button at the top of the application window.
New layer is added by clicking on a layer button with no label. This will open a dialog box where one can enter
the scene layer URL and some name. The name gets displayes on the button and is for orientation only.
Examples of scene layer URLs are:
http://scene.arcgis.com/arcgis/rest/services/Hosted/Buildings_Brest/SceneServer/layers/0
http://tiles.arcgis.com/tiles/GrCObcYo81O3Ymu8/arcgis/rest/services/North_Mine/SceneServer
http://scene.arcgis.com/arcgis/rest/services/Hosted/buildings_Indianapolis/SceneServer

- To edit the scene layer URL and Name hold down left shift + left mouse click on desired layer button
- To zoom to the extent of a layer hold down z + left mouse click on desired layer button

The application saves the configured layers, the topology and elevation states between restarts.

# Dependencies
- Qt5.7 https://www.qt.io/qt5-7/
- ArcGIS Qt SDK 100.0.0  https://developers.arcgis.com/qt/

# Deployment on Mac
- Build the eview.app in qtcreator
- In a terminal go to the build directory with the eview.app
- run deployement script
```shell
$ ../deploy.sh
```
- now you can copy and run the eview.app on another computer without the need to install the QT and ArcGIS SDKs.

