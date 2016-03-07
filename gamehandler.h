#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H
#include <QObject>
#include <iostream>
#include <vector>

#include "boxitem.h"

using namespace std;

class GameHandler:public QObject
{
    Q_OBJECT
    private:
        vector<vector<BoxItem*>> boxItems;

        int random_index(int x)
        {return(rand()%x+0);}
    public:
        explicit GameHandler(vector<vector<BoxItem*>> items,QObject *parent=0): QObject(parent){
            boxItems=items;
        }

        void startGame(){
            int i=random_index(16),j=random_index(16);
            int k=random_index(16),f=random_index(16);
            if (i==k && j==f)
                return startGame();
            boxItems[i][j]->changeValue(2);
            boxItems[k][f]->changeValue(2);
        }

        void resetGame(){
            for (int i=0;i<boxItems.size();i++)
                for (int j=0;j<boxItems[i].size();j++){
                    boxItems[i][j]->changeValue(0);
                }
        }

        void restartGame(){
            resetGame();
            startGame();
        }

        bool isFinish();


        void moveUp(){
            for (int i=1;i<boxItems.size();i++)
                for (int j=0;j<boxItems[i].size();j++)
                    if (boxItems[i][j]->getValue()==boxItems[i-1][j]->getValue()){
                        boxItems[i][j]->changeValue(0);
                        boxItems[i-1][j]->changeValue(boxItems[i-1][j]->getValue().toInt()*2);
                    }
                    else if (boxItems[i][j]->getValue()>0 && boxItems[i-1][j]->getValue()==0){
                        boxItems[i-1][j]->changeValue(2);
                        boxItems[i][j]->changeValue(0);
                    }
        }
        void moveDown(){
            for (int i=0;i<boxItems.size()-1;i++)
                for (int j=0;j<boxItems[i].size();j++)
                    if (boxItems[i][j]->getValue()==boxItems[i+1][j]->getValue()){
                        boxItems[i][j]->changeValue(0);
                        boxItems[i+1][j]->changeValue(boxItems[i+1][j]->getValue().toInt()*2);
                    }
                    else if (boxItems[i][j]->getValue()>0 && boxItems[i+1][j]->getValue()==0){
                        boxItems[i+1][j]->changeValue(2);
                        boxItems[i][j]->changeValue(0);
                    }
        }
        void moveLeft(){
            for (int i=0;i<boxItems.size();i++)
                for (int j=1;j<boxItems[i].size();j++)
                    if (boxItems[i][j]->getValue()==boxItems[i][j-1]->getValue()){
                        boxItems[i][j]->changeValue(0);
                        boxItems[i][j-1]->changeValue(boxItems[i][j-1]->getValue().toInt()*2);
                    }
                    else if (boxItems[i][j]->getValue()>0 && boxItems[i][j-1]->getValue()==0){
                        boxItems[i][j-1]->changeValue(2);
                        boxItems[i][j]->changeValue(0);
                    }
        }
        void moveRight(){
            for (int i=0;i<boxItems.size();i++)
                for (int j=0;j<boxItems[i].size()-1;j++)
                    if (boxItems[i][j]->getValue()==boxItems[i][j+1]->getValue()){
                        boxItems[i][j]->changeValue(0);
                        boxItems[i][j+1]->changeValue(boxItems[i][j+1]->getValue().toInt()*2);
                    }
                    else if (boxItems[i][j]->getValue()>0 && boxItems[i][j+1]->getValue()==0){
                        boxItems[i][j+1]->changeValue(2);
                        boxItems[i][j]->changeValue(0);
                    }
        }

    signals:
        gameIsFinish();
    public slots:
        void startGameSlot() { startGame();}
        void restartGameSlot(){ restartGame();}

        void moveUpSlot(){moveUp();}
        void moveDownSlot(){moveDown();}
        void moveLeftSlot(){moveLeft();}
        void moveRightSlot(){moveRight();}
};

#endif // GAMEHANDLER_H
