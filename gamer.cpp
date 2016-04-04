#include "gamer.h"


Gamer::Gamer(QQmlEngine *machine, QQuickItem *racine,int gridSize )
{
    _machine=machine;
    _racine=racine;
    size=gridSize;

    taille=4; //taille du Gamer par default
    readBestScore();
    startGame();

}
//gestion de la mémoire dynamique
Gamer::~Gamer()
{
    delete _machine;
    delete _racine;
    //deleteBoxItems();
}

//commence a new jeu
// initialize toutes les variables et prépare un nouveau jeu
void Gamer::startGame()
{
    vector<vector<int> > t2(taille,vector<int>(taille,0));
    history.clear();
    active=0;
    score=0;
    win=false;
    end=false;
    deleteCells();
    t=t2;

    spawnCell();
    spawnCell();

    qDebug()<<"new game";
    showCells();

}

//continue a jouer meme si on est arrivé a 2048
void Gamer::keepWin(){
    win=true;
}
bool Gamer::getWin(){
    return win;
}

int Gamer::getTaille()
{
    return taille;
}
int Gamer::getGridSize(){
    return size;
}

int Gamer::getMaxValue()
{
    int max=0;
    for(int i=0;i<taille;i++)
        for(int j=0;j<taille;j++)
            if(t[i][j]>max)
                max=t[i][j];
    return max;
}
void Gamer::setScore(int a){
    score+=a;
}
QString Gamer::getScore(){
    return QString::number(score);
}
QString Gamer::getBestScore(){
    if(score>bestScore) {
        bestScore=score;
        writeBestScore();
    }
    return QString::number(bestScore);
}

void Gamer::writeBestScore()
 {
    QSettings settings("Zanoli&Pesce", "2048 v1.0");

    settings.beginGroup("ScoreBoard");
    settings.setValue("bestScore", getBestScore());
    settings.endGroup();
}
void Gamer::readBestScore()
 {
    QSettings settings("Zanoli&Pesce", "2048 v1.0");

    settings.beginGroup("ScoreBoard");
    bestScore=settings.value("bestScore").toInt();
    settings.endGroup();
}

// change la taille du tableau et commence un nouveau jeu
void Gamer::setTaille(int tail)
{
    taille=tail;
    startGame();
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
    int stopi = i;
    bool spawned = false;
    do {
        j = random_index(taille);
        int stopj = j;
        do {
            if (t[i][j] == 0){
                if(rand()%100<90)
                    a=2;
                else
                    a=4;
                t[i][j]=a;
                spawn(i,j,a); //ajoute une nouvelle Cell dans le tableau QML
                spawned = true;
            }
            j = (j + 1) % taille;
        } while (j != stopj && !spawned);
        i = (i + 1) % taille;
    } while (i != stopi && !spawned);
    emit gotIt();
    return spawned;
}
void Gamer::showCells()
{
    uint count=0;
    for (int i=0; i<taille; i++)
        for(int j=0; j<taille; j++)
            if(t[i][j]!=0) count++;

    // si les quantités de cellules dans le moteur du jeu
    // et dans le tableau QML ne sont pas les mêmes
    // il y a un erreur
    if(c.size()!=count)
        qDebug()<<"error";

}
int Gamer::getCellIndice(int x,int y)
{
    for (uint i=0; i<c.size(); i++)
    {
        if(c[i]->getX()==x && c[i]->getY()==y && !c[i]->getMerged())
            return i;
    }
    // si la fonction ne trouve pas la Cell correspondant, il y a un problème
    // et le programme va casser
    return -1;
}

void Gamer::checkLoser(){
    vector<vector<int> > copy=t;
    for (int colmn=0;colmn<taille;colmn++)
        if (moveVert(taille-1,colmn,-1,false,false)){
            t=copy;
            return;
        }
    for (int colmn=0;colmn<taille;colmn++)
        if (moveVert(0,colmn,1,false,false)){
            t=copy;
            return;
        }
    for (int rows=0;rows<taille;rows++)
       if (moveHor(rows,taille-1,-1,false,false)){
           t=copy;
           return;
       }
    for (int rows=0;rows<taille;rows++)
        if (moveHor(rows,0,1,false,false)){
            t=copy;
            return;
        }
    end=true;

}

bool Gamer::moveVert( int x, int y, int d , bool ret,bool update)
{
    if (x<0 || x>=taille || x+d<0 || x+d>=taille)
        return ret;
    if (y<0 || y>=taille)
        return ret;
    if (t[x][y]==0)
        return moveVert(x+d,y,d,ret,update);
    moveVert(x+d,y,d,ret,update);
    if (t[x][y]==t[x+d][y] && (update ? (!c[getCellIndice(y,x+d)]->getBlock() && !c[getCellIndice(y,x)]->getBlock()) :
    true)){
        //merge
        t[x+d][y]*=2;
        t[x][y]=0;
        setScore(t[x+d][y]);
        if (update){
            c[getCellIndice(y,x+d)]->setVal(t[x+d][y]);
            c[getCellIndice(y,x+d)]->setBlock(true);
            c[getCellIndice(y,x+d)]->refreshValue();
            c[getCellIndice(y,x)]->changeMerged(true);
        }
        return moveVert(x+d,y,d,true,update);
    }
    else if (t[x+d][y]==0){
            //mouve
        t[x+d][y]=t[x][y];
        t[x][y]=0;
        if (update){
           c[getCellIndice(y,x)]->setY(x+d);
        }
           return moveVert(x+d,y,d,true,update);
    }
    else if (moveVert(x+d,y,d,false,update))
        return moveVert(x,y,d,true,update);
    return ret;
}
bool Gamer::moveHor( int x, int y, int d , bool ret,bool update)
{
    if (x<0 || x>=taille)
        return ret;
    if (y<0 || y>=taille|| y+d<0 || y+d>=taille)
        return ret;
    if (t[x][y]==0)
        return moveHor(x,y+d,d,ret,update);
    moveHor(x,y+d,d,ret,update);
    if (t[x][y]==t[x][y+d] && (update ? (!c[getCellIndice(y+d,x)]->getBlock() && !c[getCellIndice(y,x)]->getBlock()) :
    true)){
        //merge
        t[x][y+d]*=2;
        t[x][y]=0;
        setScore(t[x][y+d]);
        if (update){           
            c[getCellIndice(y+d,x)]->setVal(t[x][y+d]);
            c[getCellIndice(y+d,x)]->setBlock(true);
            c[getCellIndice(y+d,x)]->refreshValue();
            c[getCellIndice(y,x)]->changeMerged(true);
        }
        return moveHor(x,y+d,d,true,update);
    }
    else if (t[x][y+d]==0){
            //mouve
        t[x][y+d]=t[x][y];
        t[x][y]=0;
        if (update){
           c[getCellIndice(y,x)]->setX(y+d);

        }
        return moveHor(x,y+d,d,true,update);
    }
    else if (moveHor(x,y+d,d,false,update))
        return moveHor(x,y,d,true,update);
    return ret;
}

bool Gamer::up(){
    bool move=false;
    nextTable(t);
    for (int colmn=0;colmn<taille;colmn++)
        if (moveVert(taille-1,colmn,-1,false,true))
            move=true;
    if (!move)
        checkLoser();
    refresh(move);
    return true;
}
bool Gamer::down(){
    bool move=false;
    nextTable(t);
    for (int colmn=0;colmn<taille;colmn++)
        if (moveVert(0,colmn,1,false,true))
            move=true;
    if (!move)
        checkLoser();
    refresh(move);
    return true;
}
bool Gamer::left(){
    bool move=false;
    nextTable(t);
    for (int rows=0;rows<taille;rows++)
       if (moveHor(rows,taille-1,-1,false,true))
               move=true;
    if (!move)
        checkLoser();
    refresh(move);
    return true;
}
bool Gamer::right(){
    bool move=false;
    nextTable(t);
    for (int rows=0;rows<taille;rows++)
        if (moveHor(rows,0,1,false,true))
            move=true;
    if (!move)
        checkLoser();

    refresh(move);
    return true;
}

void Gamer::undo(){
    if (active-1<0)
        return;
    t=history[--active];
    history.pop_back();
    deleteCells();
    for (int i=0; i<taille; i++)
        for(int j=0; j<taille; j++)
            if(t[i][j]!=0)
                spawn(i,j,t[i][j]);

}
//enregistre l'historique du jeu
void Gamer::nextTable(vector<vector<int> > T){
    history.push_back(T);
    active++;
}

bool Gamer::gameStatus(){
    return !end;
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

//fonction qui sauvegarde le jeu dans un fichier .txt
void Gamer::saveGame(){
    std::ofstream boards;
    boards.open ("qt_sav.qm");

    nextTable(t);

    boards << history.size() << " "<<taille <<" " <<active<<" "<<win<<" ";
    qDebug()<< history.size() << " "<<taille <<" " <<active<<" "<<win<<" ";
    boards<<"\r\n"<<"\r\n"<<"\r\n";
    for(uint i=0; i<history.size(); i++)
    {

        for(uint j=0; j<history[i].size(); j++)
        {
            for(uint k=0; k<history[i][j].size(); k++)
            {
                //if (j==0 && k==0) history[i][j][k]=3;
                boards << history[i][j][k]<<" ";
                qDebug()<< history[i][j][k];
            }
            boards << "\r\n";

        }
    }
    boards.close();
    qDebug()<<"Saved";
}

//charge un jeu ancien
bool Gamer::loadGame()
{
    std::ifstream boards;
    boards.open ("qt_sav.qm");

    if(!boards.good()){ //si on a jamais sauvegardé un jeu, return false
        return false;
    }

    int nTableaux;
    t.clear();
    history.clear();
    deleteCells();

    boards >> nTableaux;
    boards >> taille;
    boards >> active;
    boards >> win;
    qDebug()<< nTableaux << " "<<taille <<" " <<active<<" "<<win<<" ";

    vector<vector<int> > t2(taille,vector<int>(taille,0));

    for(int i=0; i<nTableaux; i++)
    {
        for(int j=0; j<taille; j++)
        {
            for(int k=0; k<taille; k++)
            {
                boards >> t2[j][k];
                qDebug()<< t2[j][k];

            }
        }
        history.push_back(t2);
    }
    boards.close();

    t=history[active-1];
    score=getMaxValue();

    for(int i=0; i<taille; i++)
        for(int j=0; j<taille; j++)
            if(history[active-1][i][j] != 0)
                spawn(i,j,history[active-1][i][j]);

    emit gotIt();
    qDebug()<<"loaded";
    return true;
}
