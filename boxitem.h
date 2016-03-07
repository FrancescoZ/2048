#ifndef BOXITEM_H
#define BOXITEM_H

#include <QObject>
#include <QWidget>

class BoxItem:public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QString boxValue READ getValue NOTIFY boxChanged)
    Q_PROPERTY(QString boxBorder READ getBorder NOTIFY boxChanged)
    Q_PROPERTY(QString boxColor READ getColor NOTIFY boxChanged)
    Q_PROPERTY(bool boxVisible READ getVisible() NOTIFY boxChanged)
    private :
        QString boxColor=0,boxBorder=0,boxValue=0;
        bool boxVisible;
    public:
        explicit BoxItem(QWidget *parent=0);
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
