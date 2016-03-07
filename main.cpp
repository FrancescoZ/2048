#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QtQuick>
#include <vector>

#include "boxitem.h"
#include "gamehandler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    BoxItem box;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("viewBoxItem", &box);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    // Step 1: get access to the root object
    QObject *rootObject = engine.rootObjects().first();
    QObject *playBtn = rootObject->findChild<QQuickItem*>("startButton");
    QList<QQuickItem *> ItemGameTable = rootObject->findChild<QQuickItem*>("gameTable")->childItems();
    vector<vector<BoxItem*>> boxCases;
    for (int i=0;i<4;i++)
            boxCases.push_back(vector<BoxItem*>());

    for(int i=0;i<ItemGameTable.size();i++)
        boxCases[i/4].push_back((BoxItem *)ItemGameTable[i]);
    GameHandler *myGame=new GameHandler(boxCases,&(*rootObject));
    QObject::connect(playBtn, SIGNAL(playSignal()),
                         myGame, SLOT(startGameSlot()));

    return app.exec();
}