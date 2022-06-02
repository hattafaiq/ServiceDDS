################################################################
# Qwt Widget Library
# Copyright (C) 1997   Josef Wilgen
# Copyright (C) 2002   Uwe Rathmann
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Qwt License, Version 1.0
################################################################

include( $${PWD}/../examples.pri )

TARGET  = curvdemo1

SOURCES = \
    curvdemo1.cpp

unix:!macx: LIBS += -L$$PWD/../../../../../geserplot/libme/build-qwt-Desktop_Qt_5_12_12_GCC_64bit-Debug/lib/ -lqwt

INCLUDEPATH += $$PWD/../../../../../geserplot/libme/qwt-6.1.4/src
DEPENDPATH += $$PWD/../../../../../geserplot/libme/qwt-6.1.4/src
