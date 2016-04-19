#include "gamer.h"


Gamer::Gamer(QQmlEngine *machine, QQuickItem *racine,int gridSize )
{
    _machine=machine;
    _racine=racine;
    size=gridSize;

    taille=4; //taille du Gamer par default
    //on lis la valuer max des jeux precedents
    readBestScore();
    //on commence un jeu
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

    //on cree deux box casuelles
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

// change la taille du tableau et commence un nouveau jeu
void Gamer::setTaille(int tail)
{
    //on augmente le nombre de colon et ligne 4 min et 6 max
    if (tail>3 && tail<7){
        taille=tail;
        startGame();
    }
}
void Gamer::setScore(int a){
    score+=a;
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

//trouve à position casuelle
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
        delete c[i-1];
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
    //on regarde si on peut faire un autre mouvement, (la methode moveVert et movHor return true si elle fait de
    //changement) REMARQUE: on n'affiche pas les modifications et on ne les enregistre pas
    //UP
    for (int colmn=0;colmn<taille;colmn++)
        if (moveVert(taille-1,colmn,-1,false,false)){
            t=copy;
            return;
        }
    //DOWN
    for (int colmn=0;colmn<taille;colmn++)
        if (moveVert(0,colmn,1,false,false)){
            t=copy;
            return;
        }
    //RIGHT
    for (int rows=0;rows<taille;rows++)
       if (moveHor(rows,taille-1,-1,false,false)){
           t=copy;
           return;
       }
    //LEFT
    for (int rows=0;rows<taille;rows++)
        if (moveHor(rows,0,1,false,false)){
            t=copy;
            return;
        }
    //si on est arrivé ici veut dire que acune movuvement est possible
    end=true;

}


bool Gamer::moveVert( int x, int y, int d , bool ret,bool update)
{
    //X: est la ligne du on parte, Y: la colons,d: est l'increment qui faut faire pour controller la box succesive,
    //ret: le valeur qui il faut returner si on ne fait pas de changement
    //update nous indique si il faut afficher les modifications
    //on est sortie de la grid donc la methode est terminée
    if (x<0 || x>=taille || x+d<0 || x+d>=taille)
        return ret;
    if (y<0 || y>=taille)
        return ret;
    //si ici il n'y a rien on passe à la prochaine box
    if (t[x][y]==0)
        return moveVert(x+d,y,d,ret,update);
    //autrement on bouge toutes les box qui sont apres, faisons cela on comprende si il y a de case vide apres celle
    //ou on se trouve
    moveVert(x+d,y,d,ret,update);
    //une fois que on a bougé toutes les box apres la notre on regarde:
    //si on peut faire un merge
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
    //si on peut deplacer la box selectionnée
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
        //si on une fois avoir fait les modifications on peut encore bouger les celles apres on essie de deplacer
        //la box selectionnée
        return moveVert(x,y,d,true,update);
    return ret;
}
bool Gamer::moveHor( int x, int y, int d , bool ret,bool update)
{
    //la methode suivante est egale à moveVert mais elle controle les ligne et non le colons
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

//puor chaque methode suivant on suive ce processus:
//on enregistre la position des box actuelle
//on esseie de bouger les box selon la methode
//on verifie si nous avons perdu
//on affiche le modifications de l'engine à l'interface
bool Gamer::up(){
    bool move=false;
    nextTable(t);
    //on scan toutes les colons et pour chaque on part du bas et on monte
    for (int colmn=0;colmn<taille;colmn++)
        if (moveVert(taille-1,colmn,-1,false,true))
            move=true;
    if (!move)
        checkLoser();
    //on applique les modifications
    refresh(move);
    return true;
}
bool Gamer::down(){
    bool move=false;
    nextTable(t);
    //on scan toutes les colons et pour chaque on part du haut et on descende
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
    //on scan toutes les lignes et pour chaque on part du droit et on va vers la gauche
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
    //on scan toutes les lignes et pour chaque on part du droit et on va vers la gauche
    for (int rows=0;rows<taille;rows++)
        if (moveHor(rows,0,1,false,true))
            move=true;
    if (!move)
        checkLoser();

    refresh(move);
    return true;
}


void Gamer::undo(){
    //chaque fois on efface tout les box et on les affiche à nouveau
    if (active-1<0)
        return;
    t=history[--active];
    score=scoreHistory[--active];
    scoreHistory.pop_back();
    history.pop_back();
    deleteCells();
    for (int i=0; i<taille; i++)
        for(int j=0; j<taille; j++)
            if(t[i][j]!=0)
                spawn(i,j,t[i][j]);
     emit gotIt();

}
//enregistre l'historique du jeu
void Gamer::nextTable(vector<vector<int> > T){
    history.push_back(T);
    scoreHistory.push_back(score);
    active++;
}

bool Gamer::gameStatus(){
    return !end;
}

void Gamer::refresh(bool move){
    //met à jour les positions du tableau QML et debloque les box qui ont été merged
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
    //on enregistre touts les mouvement et les scores grace à une fonctionnalité de QT qui permet d'enregister de
    //donnés sans utiliser de fiche
    std::ofstream boards;
    boards.open ("qt_sav.qm");

    nextTable(t);

    boards << history.size() << " "<<taille <<" " <<active<<" "<<win<<" ";
    boards<<"\r\n"<<"\r\n"<<"\r\n";
    for(uint i=0; i<history.size(); i++)
    {

        for(uint j=0; j<history[i].size(); j++)
        {
            for(uint k=0; k<history[i][j].size(); k++)
            {
                boards << history[i][j][k]<<" ";
            }
            boards << "\r\n";

        }
    }
    for(uint i=0; i<history.size(); i++)
        boards << scoreHistory[i]<<" ";
    boards.close();
    qDebug()<<"Saved";
}

//charge un jeu ancien
bool Gamer::loadGame()
{
    //on sauvegarder au contraire de l'enregistrement
    std::ifstream boards;
    boards.open ("qt_sav.qm");

    if(!boards.good()){ //si on a jamais sauvegardé un jeu, return false
        return false;
    }

    int nTableaux;
    t.clear();
    history.clear();
    scoreHistory.clear();
    deleteCells();

    boards >> nTableaux;
    boards >> taille;
    boards >> active;
    boards >> win;

    vector<vector<int> > t2(taille,vector<int>(taille,0));

    for(int i=0; i<nTableaux; i++)
    {
        for(int j=0; j<taille; j++)
            for(int k=0; k<taille; k++)
                boards >> t2[j][k];
        history.push_back(t2);
    }
    for(int i=0; i<nTableaux; i++)
    {
        int a=0;
        boards >> a;
        scoreHistory.push_back(a);
    }
    boards.close();

    t=history[active-1];
    score=scoreHistory[active-1];

    for(int i=0; i<taille; i++)
        for(int j=0; j<taille; j++)
            if(history[active-1][i][j] != 0)
                spawn(i,j,history[active-1][i][j]);

    emit gotIt();
    qDebug()<<"loaded";
    return true;
}
