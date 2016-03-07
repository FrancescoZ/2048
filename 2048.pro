TEMPLATE = app

QT += qml quick
QT += widgets

CONFIG += c++11

SOURCES += main.cpp \
    boxitem.cpp \
    gamehandler.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES +=

HEADERS += \
    boxitem.h \
    gamehandler.h
