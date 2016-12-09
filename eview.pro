mac {
    cache()
}

#-------------------------------------------------------------------------------

CONFIG += c++11 arcgis_runtime_qml_cpp100_0_0

QT += opengl qml quick positioning sensors

TEMPLATE = app
TARGET = eview

#-------------------------------------------------------------------------------

HEADERS += \
    eview.h \
    dialog.h

SOURCES += \
    main.cpp \
    eview.cpp \
    dialog.cpp

RESOURCES += eview.qrc

#-------------------------------------------------------------------------------

win32 {
    LIBS += \
        Ole32.lib
}

#ios {
#    INCLUDEPATH += $$PWD
#    DEPENDPATH += $$PWD

#    OTHER_FILES += \
#        $$PWD/Info.plist

#    QMAKE_INFO_PLIST = $$PWD/Info.plist
#}

#android {
#    INCLUDEPATH += $$PWD
#    DEPENDPATH += $$PWD
#}

macx {
   QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.11
}

FORMS += \
    dialog.ui

DISTFILES += \
    URLEditForm.ui.qml \
    URLEdit.qml
