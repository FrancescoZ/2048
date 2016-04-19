#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QtQuick>
#include <QtCore>
#include <QtGui>
#include "time.h"

#include "gamer.h"

int main(int argc, char *argv[])
{
    //Initialisation de l'interface utilisateur
    QGuiApplication app(argc, argv);
    QQuickView viewer;

    //initialisation de la fonction rand pour avoir des valeurs vraiment aléatoires
    srand(time(NULL));
    qsrand(time(NULL));

    //Nous disons quelle forme doit avoir l'interface
    viewer.setSource(QUrl(QStringLiteral("qrc:/main.qml")));

    //Nous prendons les objet principales pour pouvoir gerer ensuite l'interface
    QQuickItem *root = viewer.rootObject();
    QQmlEngine *engine = viewer.engine();

    //Objet qui gere tout le joue, on le lie à l'interface
    Gamer gamer(engine, root,450);
    viewer.rootContext()->setContextProperty("gamer", &gamer);

    //on montre l'interface chargé
    viewer.show();

    return app.exec();
}
