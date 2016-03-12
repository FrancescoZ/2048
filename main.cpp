#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QtQuick>
#include <QtCore>
#include <QtGui>
#include <QGridLayout>

#include <vector>
#include <list>

#include "boxitem.h"
#include "gamehandler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    GameHandler *gameBrain=new GameHandler;
    engine.rootContext()->setContextProperty("viewTable", gameBrain);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    // Step 1: get access to the root object
    QObject *playBtn = engine.rootObjects().first()->findChild<QQuickItem*>("startButton");

    QObject::connect(playBtn, SIGNAL(playSignal()),
                         gameBrain, SLOT(startGameSlot()));

    return app.exec();
}
