#ifndef GAMER_H
#define GAMER_H

#include <QObject>
#include <QQuickItem>
#include <vector>
#include <QSettings>
#include <fstream>
#include <QQmlEngine>
#include "boxitem.h"

using namespace std;

class Gamer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString vScore READ getScore NOTIFY gotIt)
    Q_PROPERTY(QString vBestScore READ getBestScore NOTIFY gotIt)
    Q_PROPERTY(int getTaille READ getTaille NOTIFY gotIt)
    Q_PROPERTY(int getGridSize READ getGridSize NOTIFY gotIt)

public:

    Gamer( QQmlEngine* machine, QQuickItem* racine,int gridSize);
    ~Gamer();

    void nextTableau(vector<vector<int> > T);

    Q_INVOKABLE void startGame();
    Q_INVOKABLE void setTaille(int);
    int getTaille();
    int getGridSize();

    Q_INVOKABLE void keepWin();
    Q_INVOKABLE bool getWin();

    Q_INVOKABLE QString getScore();
    Q_INVOKABLE int getMaxValue();

    int random_index(int);

    QString getBestScore();


    Q_INVOKABLE bool gameStatus();
    Q_INVOKABLE bool up();
    Q_INVOKABLE bool down();
    Q_INVOKABLE bool left();
    Q_INVOKABLE bool right();
    Q_INVOKABLE void deleteCells();

    Q_INVOKABLE bool animRunning();

private:
    QQmlEngine* _machine; //garde l'engine de la partie graphique
    QQuickItem* _racine; //garde la racine de la partie graphique

    void spawn(int, int, int);

    vector <BoxItem*> c; //garde les cellules qui sont sur le tableau

    vector<vector<vector<int> > > history; //garde toutes les pas du jeu
    vector<vector<int> > t; //tableau avec les pas actuels
    vector<int> scores; //vecteur avec les score à chaque pas

    int active; //garde le tableau active
    bool win; //indique si le 2048 a déjà été formé
    bool end;
    int taille; //garde la taille du tableau
    int size;//taille de la grid
    int score; // garde le score actuel
    int bestScore; //garde le best Score

    int getCellIndice(int x,int y,bool  unMerged=false);
    void checkLoser();
    bool moveVert( int x, int y, int d , bool ret,bool update);
    bool moveHor( int x, int y, int d , bool ret,bool update);
    void showCells();

    bool spawnCell();

    void readBestScore();
    void writeBestScore();

    void refresh(bool move);
signals:
    void gotIt();

};
#endif // GAMER_H
