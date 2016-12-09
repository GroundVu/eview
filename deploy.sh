

# Must be run in directory with the eview.app

${HOME}/Qt/5.7/clang_64/bin/macdeployqt eview.app/ -qmldir=../eview/ -always-overwrite -verbose=1 > install.txt 2>&1

install_name_tool -change ${HOME}/ArcGIS_SDKs/Qt100.0/sdk/macos/x64/lib/libEsriCommonQt.dylib @rpath/libEsriCommonQt.dylib eview.app/Contents/MacOS/eview

otool -L eview.app/Contents/MacOS/eview 
