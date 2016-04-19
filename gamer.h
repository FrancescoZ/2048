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
    //La classe suivante gere toute les interaction entre l'engine de jeu et l'interface Utilisateur, d'abord
    //on calcule les modification à faire sur le tableau t et ensuite on les applique à l'interface
    Q_OBJECT

    //resultat
    Q_PROPERTY(QString vScore READ getScore NOTIFY gotIt)
    Q_PROPERTY(QString vBestScore READ getBestScore NOTIFY gotIt)
    //dimension
    Q_PROPERTY(int getTaille READ getTaille NOTIFY gotIt)
    Q_PROPERTY(int getGridSize READ getGridSize NOTIFY gotIt)

public:

    Gamer( QQmlEngine* machine, QQuickItem* racine,int gridSize);
    ~Gamer();

    //memorise le tableau actuel pour pouvoir revenir en arrier
    void nextTable(vector<vector<int> > T);

    //lance le signal pour pouvoir commencer le jeu
    Q_INVOKABLE void startGame();

    //proprietes setter
    Q_INVOKABLE void setTaille(int);
    Q_INVOKABLE void setScore(int a);

    //proprietes getter
    int getTaille();
    int getGridSize();
    QString getBestScore();
    Q_INVOKABLE QString getScore();
    Q_INVOKABLE int getMaxValue();

    Q_INVOKABLE void keepWin();
    Q_INVOKABLE bool getWin();

    int random_index(int);

    //enregistre le jeu et recharge les enregistrement
    Q_INVOKABLE void saveGame();
    Q_INVOKABLE bool loadGame();

    //le jeu est-il fini?
    Q_INVOKABLE bool gameStatus();
    //appuie des flash de clavier
    Q_INVOKABLE bool up();
    Q_INVOKABLE bool down();
    Q_INVOKABLE bool left();
    Q_INVOKABLE bool right();

    //efface toutes les box
    Q_INVOKABLE void deleteCells();

    //retourn en arrier
    Q_INVOKABLE void undo();

    //controle si le animations sont en esecution
    Q_INVOKABLE bool animRunning();

private:
    QQmlEngine* _machine; //garde l'engine de la partie graphique
    QQuickItem* _racine; //garde la racine de la partie graphique

    //cree une nouvelle box en position indique avec la valeur donné
    void spawn(int, int, int);
    //cree une nouvelle box en postion casuelle
    bool spawnCell();

    vector <BoxItem*> c; //garde les cellules qui sont sur le tableau

    vector<vector<vector<int> > > history; //garde toutes les pas du jeu
    vector<int> scoreHistory;//garde le score pour chaque tableau
    vector<vector<int> > t; //tableau avec les pas actuels

    int active; //garde le tableau active
    bool win; //indique si le 2048 a déjà été formé
    bool end;//indique si le jeu est terminé
    int taille; //garde la taille du tableau
    int size;//taille de la grid
    int score; // garde le score actuel
    int bestScore; //garde le best Score

    //Cherche le box en position x, y dans la list de toutes les boxs
    int getCellIndice(int x,int y);

    //verifie si le jeu est terminé
    void checkLoser();

    //methodes recoursives pour deplacer les boxes
    bool moveVert( int x, int y, int d , bool ret,bool update);
    bool moveHor( int x, int y, int d , bool ret,bool update);

    //Verifie si il y a des erreurs avant d'affiche le modification
    void showCells();

    //enregistre et lis le meilleur resultat
    void readBestScore();
    void writeBestScore();

    //recharge l'interface graphique
    void refresh(bool move);
signals:
    //signal pour indique à l'interface qui il y a eu des modifications
    void gotIt();

};
#endif // GAMER_H
