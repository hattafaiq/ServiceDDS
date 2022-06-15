QT += gui
QT += core websockets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    libme/fft/fourierd.c\
    libme/fft/fftmisc.c\
    libme/windowing/windowkan.c\
    libme/windowing/buat_filter.c\
    signalprocessing.cpp \
    grafik.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    libme/windowing/windowkan.h \
    libme/windowing/buat_filter.h \
    signalprocessing.h \
    datasetup.h \
    grafik.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

#ICON = icon.icns

#RESOURCES += \
#    icon.qrc

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

unix:INCLUDEPATH +=$$PWD/libme/qwt-6.1.4/src
##unix:INCLUDEPATH +=$$FOLDER/qt_lib/mupdf-qt/include
unix: LIBS += -L$$PWD/libme/build-qwt-Desktop_Qt_5_12_12_GCC_64bit-Debug/lib -lqwt
