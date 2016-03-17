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
    void setX(int);
    void setY(int);
    void setVal(int);
    void refreshPosition();
    void refreshValue();

    bool getMerged();
    void changeMerged(bool);
    bool getMerged2();
    void changeMerged2(bool);
    bool getUnMerged();
    void changeUnMerged(bool);

     bool getAnimRunning();

private:
    QQuickItem *object; //variable qui est liée à la partie graphique
    int x; //garde la position x
    int y; // garde la position y
    int value; //garde la valeur
    vector<int> placement; //garde les coordonées du tableau en fonction de la taille
    bool merged; //true si elle a été mergé et doit être supprimé
    bool merged2; //true si elle a été mergé et doit avoir sa valeur mise à jour
    bool unMerged; //true si elle vient d'être "unmergé"
    int taille; //taille du tableau

    // garde les animations
    QObject *hAni;
    QObject *wAni;
    QObject *xAni;
    QObject *yAni;

};

#endif // BOXITEM_H
