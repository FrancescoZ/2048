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

    BoxItem box;
    engine.rootContext()->setContextProperty("viewBoxItem", &box);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));



    // Step 1: get access to the root object
    QObject *rootObject = engine.rootObjects().first();
    QObject *playBtn = rootObject->findChild<QQuickItem*>("startButton");

    vector<vector<BoxItem*>> boxCases;
    QObject *q=rootObject->findChild<QQuickItem*>("repBox");
    /*vector<BoxItem *>ItemGameTable;
    for (int i=0;i<16;i++){
            ItemGameTable.push_back(new BoxItem());

            ((QGridLayout *)q)->addWidget(ItemGameTable[i],i/4,i%4);
    }


    for (int i=0;i<4;i++)
            boxCases.push_back(vector<BoxItem*>());
    for(int i=0;i<ItemGameTable.size();i++)
        boxCases[i/4].push_back(ItemGameTable[i]);*/

    GameHandler *myGame=new GameHandler(boxCases,&(*rootObject));
    QObject::connect(playBtn, SIGNAL(playSignal()),
                         myGame, SLOT(startGameSlot()));

    return app.exec();
}
