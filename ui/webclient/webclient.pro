QT -= gui
QT += core websockets

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        client.cpp \
        main.cpp

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

HEADERS += \
    client.h \
    datasetup.h

unix:INCLUDEPATH +=$$PWD/lib/qwt-6.1.4/src
##unix:INCLUDEPATH +=$$FOLDER/qt_lib/mupdf-qt/include
unix: LIBS += -L$$PWD/lib/build-qwt-Desktop_Qt_5_12_12_GCC_64bit-Debug/lib -lqwt