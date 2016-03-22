#include "gamer.h"


Gamer::Gamer(QQmlEngine *machine, QQuickItem *racine,int gridSize )
{
    _machine=machine;
    _racine=racine;
    size=gridSize;

    taille=4; //taille du Gamer par default
    startGame();

}

//gestion de la mémoire dynamique
Gamer::~Gamer()
{
    delete _machine;
    delete _racine;
    //deleteBoxItems();
}

// initialize toutes les variables et prépare un nouveau jeu
void Gamer::startGame()
{
    vector<vector<int> > t2(taille,vector<int>(taille,0));
    vector<vector<bool> >  merged(taille,vector<bool>(taille,false));

    tableaux.clear();
    vecMerged.clear();
    vecInc.clear();
    vecRC.clear();
    scores.clear();
    spawnedCOL.clear();
    spawnedROW.clear();
    active=-1;
    score=0;
    win=false;

    deleteCells();

    nextTableau(t2);
    spawnedCOL.push_back(0);
    spawnedROW.push_back(0);


    spawnCell();

    spawnCell();

    qDebug()<<"new game";
    showCells();

}

int Gamer::getTaille()
{
    return taille;
}
int Gamer::getGridSize(){
    return size;
}
int Gamer::random_index(int x)
{
    int index;
    srand(rand());
    index=rand()%x+0;
    return index;
}
//supprime toutes les Cells du vecteur c
void Gamer::deleteCells()
{
    for (int i=c.size(); i>0; i--)
    {
        delete c[i-1];
    }
    c.clear();
}

// fonction qui va ajouter le nouveau tableau dans les vecteurs qui gardent les pas du jeu
void Gamer::nextTableau(vector<vector<int> > T)
{
    //si on a fait précedent, et on joue, on supprime toutes les pas postérieures
    if(tableaux.size()>active+1)
    {
        int tamanho=tableaux.size()-(active+1);
        for( int i=0; i<tamanho ; i++){
            tableaux.pop_back();
            scores.pop_back();
            vecInc.pop_back();
            vecMerged.pop_back();
            vecRC.pop_back();
            spawnedCOL.pop_back();
            spawnedROW.pop_back();
        }
    }

    tableaux.push_back(T);
    active++;
    t=tableaux[active];

}

//fonction qui ajoute une nouvelle Cell au tableau dans la position (j,i) avec la valeur a
void Gamer::spawn(int i, int j, int a)
{
    c.push_back(new BoxItem(_machine,_racine,i,j,a,taille,size));
}
// crée une nouvelle celule dans une position libre aléatoire
bool Gamer::spawnCell(){
    int i = random_index(taille);;
    int j;
    int a;
    //t = tableaux[active];
    int stopi = i;

    bool spawned = false;

    do {
        j = random_index(taille);
        int stopj = j;

        do {
            if (t[i][j] == 0){

                if(rand()%100<90){
                a=2;}
                else {a=4;}
                t[i][j]=a;

                if(active>0)
                {
                    spawnedCOL.push_back(j);
                    spawnedROW.push_back(i);
                }

                spawn(i,j,a); //ajoute une nouvelle Cell dans le tableau QML

                spawned = true;
            }

            j = (j + 1) % taille;
        } while (j != stopj && !spawned);

        i = (i + 1) % taille;
    } while (i != stopi && !spawned);

    //tableaux[active]=t;
    emit gotIt();

    return spawned;
}
void Gamer::showCells()
{
    int count=0;
    for (int i=0; i<taille; i++)
        for(int j=0; j<taille; j++)
            if(tableaux[active][i][j]!=0) count++;

    // si les quantités de cellules dans le moteur du jeu
    // et dans le tableau QML ne sont pas les mêmes
    // il y a un erreur
    if(c.size()!=count) qDebug()<<"error";

}
int Gamer::getCellIndice(int x,int y, bool unMerged)
{
    for (int i=0; i<c.size(); i++)
    {
        if(c[i]->getX()==x && c[i]->getY()==y && !c[i]->getMerged())
            return i;
    }
    // si la fonction ne trouve pas la Cell correspondant, il y a un problème
    // et le programme va casser
    return -1;
}

bool Gamer::moveVert( int x, int y, int d , bool ret)
{
    if (x<0 || x>=taille || x+d<0 || x+d>=taille)
        return ret;
    if (y<0 || y>=taille)
        return ret;
    if (t[x][y]==0)
        return moveVert(x+d,y,d,ret);
    else if (t[x][y]==t[x+d][y] && !c[getCellIndice(y,x+d)]->getBlock()){
        //merge
        t[x+d][y]*=2;
        t[x][y]=0;
        c[getCellIndice(y,x+d)]->setVal(t[x+d][y]);
        c[getCellIndice(y,x+d)]->setBlock(true);
        c[getCellIndice(y,x+d)]->refreshValue();
        c[getCellIndice(y,x)]->changeMerged(true);
        return moveVert(x+d,y,d,true);
    }
    else if (t[x+d][y]==0){
            //mouve
           c[getCellIndice(y,x)]->setY(x+d);
           t[x+d][y]=t[x][y];
           t[x][y]=0;
           return moveVert(x+d,y,d,true);
    }
    else if (moveVert(x+d,y,d,false))
        return moveVert(x,y,d,true);
    return ret;
}
bool Gamer::moveHor( int x, int y, int d , bool ret)
{
    if (x<0 || x>=taille)
        return ret;
    if (y<0 || y>=taille|| y+d<0 || y+d>=taille)
        return ret;
    if (t[x][y]==0)
        return moveHor(x,y+d,d,ret);
    else if (t[x][y]==t[x][y+d] && !c[getCellIndice(y+d,x)]->getBlock()){
        //merge
        t[x][y+d]*=2;
        t[x][y]=0;
        c[getCellIndice(y+d,x)]->setVal(t[x][y+d]);
        c[getCellIndice(y+d,x)]->setBlock(true);
        c[getCellIndice(y+d,x)]->refreshValue();
        c[getCellIndice(y,x)]->changeMerged(true);
        return moveHor(x,y+d,d,true);
    }
    else if (t[x][y+d]==0){
            //mouve
           c[getCellIndice(y,x)]->setX(y+d);
           t[x][y+d]=t[x][y];
           t[x][y]=0;
           return moveHor(x,y+d,d,true);
    }
    else if (moveHor(x,y+d,d,false))
        return moveHor(x,y,d,true);
    return ret;
}

bool Gamer::up(){
    bool move=false;
    for (int colmn=0;colmn<taille;colmn++)
        if (moveVert(taille-1,colmn,-1,false))
            move=true;
    refresh(move);
    return true;
}
bool Gamer::down(){
    bool move=false;
    for (int colmn=0;colmn<taille;colmn++)
        if (moveVert(0,colmn,1,false))
            move=true;
    refresh(move);
    return true;
}
bool Gamer::left(){
    bool move=false;
    for (int rows=0;rows<taille;rows++)
       if (moveHor(rows,taille-1,-1,false))
               move=true;
    refresh(move);
    return true;
}
bool Gamer::right(){
    bool move=false;
    for (int rows=0;rows<taille;rows++)
        if (moveHor(rows,0,1,false))
            move=true;
    refresh(move);
    return true;
}

void Gamer::refresh(bool move){
    //met à jour les positions du tableau QML
    for(int i=c.size()-1; i>=0; i--){
        c[i]->refreshPosition();
        c[i]->setBlock(false);
    }
    //supprime les Cells mergées
    for(int i=c.size()-1; i>=0; i--)
        if(c[i]->getMerged())
        {
            delete c[i];
            c.erase(c.begin() + i);
        }
    if (move)
        spawnCell();
}

bool Gamer::animRunning()
{
    for(int i=c.size()-1; i>=0; i--)
        if(c[i]->getAnimRunning())
            return true;
    return false;
}
