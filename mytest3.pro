QT += core widgets gui webkitwidgets network

TARGET = mytest3

CONFIG += c++11


TEMPLATE = app

SOURCES += main.cpp \
    window.cpp \
    helper.cpp

HEADERS += \
    window.h \
    helper.h

RESOURCES += \
    resource.qrc

