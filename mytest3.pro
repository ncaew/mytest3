
QT += core widgets gui webkitwidgets network websockets

TARGET = mytest3

CONFIG += c++11


TEMPLATE = app

SOURCES += main.cpp \
    window.cpp \
    helper.cpp \
    assist.cpp

HEADERS += \
    window.h \
    helper.h \
    assist.h

RESOURCES += \
    resource.qrc


