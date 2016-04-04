#ifndef BOXITEM_H
#define BOXITEM_H

#include <QQuickItem>
#include <vector>

using namespace std;

class BoxItem: public QQuickItem
{
    Q_OBJECT
public:
    BoxItem(QQmlEngine*, QQuickItem *, int , int , int , int, int);
    ~BoxItem();
    void destroy();

    int getX();
    int getY();
    int getVal();
    bool getBlock();

    void setBlock(bool);
    void setX(int);
    void setY(int);
    void setVal(int);

    void refreshPosition();
    void refreshValue();

    bool getMerged();
    void changeMerged(bool);

     bool getAnimRunning();

private:
    QQuickItem *object; //variable qui est liée à la partie graphique
    int x; //garde la position x
    int y; // garde la position y
    int value; //garde la valeur
    bool block; //empeche le merge multiple pour chaque mouvement
    vector<int> placement; //garde les coordonées du tableau en fonction de la taille
    bool merged; //true si elle a été mergé et doit être supprimé
    int taille; //taille du tableau

    // garde les animations
    QObject *hAni;
    QObject *wAni;
    QObject *xAni;
    QObject *yAni;
    QObject *cAni;

};

#endif // BOXITEM_H
