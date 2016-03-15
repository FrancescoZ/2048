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

    nextTableau(t2,merged,false,0);
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
void Gamer::nextTableau(vector<vector<int> > T, vector<vector<bool> > merged, bool selectorRC, int inc)
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
    scores.push_back(score);
    vecMerged.push_back(merged);
    vecInc.push_back(inc);
    vecRC.push_back(selectorRC);

    //vérifie le bestScore
    if(score>bestScore) {
        bestScore=score;
        writeBestScore();
    }


    active++;


    t=tableaux[active];
    score=scores[active];
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
    t = tableaux[active];
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

    tableaux[active]=t;
    emit gotIt();

    return spawned;
}

void Gamer::showCells()
{
    int count=0;
    for (int i=0; i<taille; i++)
    {
        for(int j=0; j<taille; j++)
        {
            if(tableaux[active][i][j]!=0) count++;
        }
    }
    // si les quantités de cellules dans le moteur du jeu
    // et dans le tableau QML ne sont pas les mêmes
    // il y a un erreur
    if(c.size()!=count) qDebug()<<"error";

}



bool Gamer::up(){
    return iterateRC(0, 0, false, 1);}

bool Gamer::down(){
    return iterateRC (taille-1, 0, false, -1);
}

bool Gamer::left(){
    return iterateRC (0, 0, true, 1);
}

bool Gamer::right(){
    return iterateRC (0, taille-1, true, -1);
}
bool Tableau::iterateRC(int row, int col, bool selectorRC, int inc, bool update, bool nTab){

    bool need2spawn = false;
    bool ret=false;
    vector<vector<bool> > merged(taille,vector<bool>(taille,false));

    //itérations qui font la mécanique du jeu
    for(; (selectorRC ? row < taille : col < taille);
        (selectorRC ? row ++ : col ++)) {

        ret = move (row, col, selectorRC, inc, update);
        need2spawn = ret || need2spawn;
        ret = merge (row, col, selectorRC, inc, update);
        need2spawn = ret || need2spawn;
        ret = move (row, col, selectorRC, inc, update);
        need2spawn = ret || need2spawn;
    }

    //si un mouvement a été fait, on met à jour le tableau
    if (need2spawn && update)
    {
        if(nTab) //si ce n'est pas la fonction redo()
        {
            // crée un nouveau tableau mergé, qui indique où il y a eu des fusions
            for(int i=c.size()-1; i>=0; i--) {

                if(c[i]->getMerged2())
                {
                    merged[c[i]->getY()][c[i]->getX()]=true;
                }

            }
            //sauvegarde le prochain tableau
            nextTableau(t,merged,selectorRC,inc);
        }

        //met à jour les positions du tableau QML
        for(int i=c.size()-1; i>=0; i--) {

            c[i]->refreshPosition();

        }

        //met à jour les valeurs du tableau QML
        for(int i=c.size()-1; i>=0; i--) {

            if(c[i]->getMerged2())
            {
                c[i]->refreshValue();
                c[i]->changeMerged2(false);
            }

        }
        //supprime les Cells mergées
        for(int i=c.size()-1; i>=0; i--) {

            if(c[i]->getMerged())
            {
                delete c[i];
                c.erase(c.begin() + i);
            }

        }
        // crée une nouvelle cellule
        if(nTab) spawnCell();
        // "respawn" la cellule (cas redo())
        else spawn(spawnedROW[active],spawnedCOL[active],tableaux[active][spawnedROW[active]][spawnedCOL[active]]);


    }
    // vérifie si il n'y a pas des erreurs (plus utile maintenant)
    if(update) {
        showCells();
    }

    return need2spawn;
}
