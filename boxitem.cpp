#include "boxitem.h"

BoxItem::BoxItem(QQmlEngine *machine, QQuickItem *racine, int i, int j, int a, int Size,int gridSize)
{
    QQmlComponent component(machine, QUrl(QStringLiteral("qrc:/Box.qml")));

    //
    object = qobject_cast<QQuickItem*>(component.create());

    object->setProperty("visibilite", false);
    object->setParentItem(racine->findChild<QQuickItem*>("grid"));

    taille=Size;

    for(int k=0; k<taille; k++)
        placement.push_back(8+gridSize*k/taille);

    object->setProperty("size", gridSize/taille-6);
    object->setProperty("taille", 1);

    object->setProperty("val_x", placement[j]);
    object->setProperty("val_y", placement[i]);

    object->setProperty("valeur", a);

    x=j;
    y=i;
    value=a;

    object->setProperty("visibilite", true);
    object->setProperty("taille", 424/taille-6);
    merged=false;
    merged2=false;
    unMerged=false;
}

BoxItem::~BoxItem()
{
    destroy();
}
void BoxItem::destroy()
{
    delete object;
}

int BoxItem::getX()
{
    return x;
}

int BoxItem::getY()
{
    return y;
}

int BoxItem::getVal()
{
    return value;
}

void BoxItem::setX(int nX)
{
    x=nX;
}

void BoxItem::setY(int nY)
{
    y=nY;
}

void BoxItem::setVal(int nVal)
{
    value=nVal;
}
void BoxItem::refreshPosition()
{
    object->setProperty("val_x", placement[x]);
    object->setProperty("val_y", placement[y]);

}
void BoxItem::refreshValue()
{
    object->setProperty("taille", 430/taille);
    object->setProperty("valeur", value);
    object->setProperty("taille", 424/taille-6);

   //qDebug()<<"refreshed";

}


bool BoxItem::getMerged()
{
    return merged;
}

void BoxItem::changeMerged(bool a)
{
    merged=a;
}
bool BoxItem::getMerged2()
{
    return merged2;
}

void BoxItem::changeMerged2(bool a)
{
    merged2=a;
}

bool BoxItem::getAnimRunning()
{

    /*if(hAni!=NULL && hAni->property("running").toBool()) return true;
    if(wAni!=NULL && wAni->property("running").toBool()) return true;
    if(xAni!=NULL && xAni->property("running").toBool()) return true;
    if(yAni!=NULL && yAni->property("running").toBool()) return true;
*/
    return false;

}

bool BoxItem::getUnMerged()
{
    return unMerged;
}

void BoxItem::changeUnMerged(bool a)
{
    unMerged=a;
}
