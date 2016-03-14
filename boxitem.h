#ifndef BOXITEM_H
#define BOXITEM_H

#include <QObject>
#include <QWidget>

class BoxItem:public QObject
{
    Q_OBJECT

    private :
        QString boxColor=0,boxBorder=0,boxValue=0;
        bool boxVisible;
    public:
        // Copy constructor
        BoxItem(const BoxItem &cSource)
        {
            this->boxValue=cSource.boxValue;
            UpdateBox();
        }

        BoxItem& operator= (const BoxItem &cSource){
            this->boxValue=cSource.boxValue;
            UpdateBox();
            return *this;
        }
        explicit BoxItem(QObject *parent=0);
        void UpdateBox(){
            emit boxChanged();
        }

        QString getValue(){
            return boxValue;
        }
        QString getBorder(){
            return boxBorder;
        }
        QString getColor(){
            return boxColor;
        }
        bool getVisible(){
            return boxVisible;
        }

        void changeVisibility(bool value){
            boxVisible=value;
            UpdateBox();
        }

        void changeValue(int value){
            if (value%2!=0)
                changeVisibility(false);
            boxValue=QString::number(value);
            changeVisibility(true);
            UpdateBox();
        }

    signals:
        void boxChanged();
};

#endif // BOXITEM_H
