QT += gui
QT += core websockets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    datasetup.h \
    mainwindow.h

FORMS += \
    mainwindow.ui


unix:!macx: LIBS += -L$$PWD/../NEWclient/libme/build-qwt-Desktop_Qt_5_12_12_GCC_64bit-Debug/lib/ -lqwt

INCLUDEPATH += $$PWD/../NEWclient/libme/qwt-6.1.4/src
DEPENDPATH += $$PWD/../NEWclient/libme/qwt-6.1.4/src
