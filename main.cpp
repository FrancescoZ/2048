#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QtQuick>
#include <QtCore>
#include <QtGui>

#include "gamer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickView viewer;

    //initialisation de la fonction rand pour avoir des valeurs vraiment aléatoires
    srand(time(NULL));
    qsrand(time(NULL));

    viewer.setSource(QUrl(QStringLiteral("qrc:/main.qml")));

    QQuickItem *root = viewer.rootObject();
    QQmlEngine *engine = viewer.engine();

    Gamer gamer(engine, root,450);
    viewer.rootContext()->setContextProperty("gamer", &gamer);

    viewer.show();

    return app.exec();
}
