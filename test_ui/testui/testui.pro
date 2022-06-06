QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../DDS_JSON/UIClientREALDATA/libme/build-qwt-Desktop_Qt_5_12_12_GCC_64bit-Debug/lib/release/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../DDS_JSON/UIClientREALDATA/libme/build-qwt-Desktop_Qt_5_12_12_GCC_64bit-Debug/lib/debug/ -lqwt
else:unix: LIBS += -L$$PWD/../../DDS_JSON/UIClientREALDATA/libme/build-qwt-Desktop_Qt_5_12_12_GCC_64bit-Debug/lib/ -lqwt

INCLUDEPATH += $$PWD/../../DDS_JSON/UIClientREALDATA/libme/qwt-6.1.4/src
DEPENDPATH += $$PWD/../../DDS_JSON/UIClientREALDATA/libme/qwt-6.1.4/src
