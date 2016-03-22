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
    Q_INVOKABLE void setTaille(int){}
    int getTaille();
    Q_INVOKABLE void setGrisSize(int){}
    int getGridSize();
    Q_INVOKABLE void suivant(){}
    Q_INVOKABLE void gagnant(){}
    Q_INVOKABLE bool getWin(){return false;}
    Q_INVOKABLE void precedent(){}

    Q_INVOKABLE void saveGame(){}
    Q_INVOKABLE bool loadGame(){return false;}

    Q_INVOKABLE QString getScore(){}
    Q_INVOKABLE int getMaxValue(){return 8;}

    int random_index(int);

    QString getBestScore(){return "2";}

    void setActive(int ){}
    Q_INVOKABLE bool gameStatus(){return true;}

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

    vector<vector<vector<int> > > tableaux; //garde toutes les pas du jeu
    int active; //garde le tableau active
    bool win; //indique si le 2048 a déjà été formé
    int taille; //garde la taille du tableau
    int size;//taille de la grid
    int score; // garde le score actuel
    int bestScore; //garde le best Score
    vector<int> scores; //vecteur avec les score à chaque pas
    vector<vector<int> > t; //tableau avec les pas actuels
    vector<vector<vector<bool> > > vecMerged; //garde les emplacements où il y a eu des "merges" à chaque pas
    vector<int> vecInc; //garde la direction du pas
    vector<bool> vecRC; //garde si c'est colonne ou ligne
    vector<int> spawnedROW; //garde la coordonné y de la cellule "spawned" dans chaque pas
    vector<int> spawnedCOL; //garde la coordonné x de la cellule "spawned" dans chaque pas

    int getCellIndice(int x,int y,bool  unMerged=false);
    bool moveVert( int x, int y, int d , bool ret);
    bool moveHor( int x, int y, int d , bool ret);
    void showCells();
    void undo(){}
    void redo(){}
    void unmergeCell(int row, int col){}

    bool spawnCell();
    void readBestScore(){}
    void writeBestScore(){}

    void refresh(bool move);
signals:
    void gotIt();

};
#endif // GAMER_H
