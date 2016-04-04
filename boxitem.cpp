#include "boxitem.h"

BoxItem::BoxItem(QQmlEngine *machine, QQuickItem *racine, int i, int j, int a, int Size,int gridSize)
{
    QQmlComponent component(machine, QUrl(QStringLiteral("qrc:/Box.qml")));

    //
    object = qobject_cast<QQuickItem*>(component.create());

    object->setProperty("visibilite", false);
    object->setProperty("opacity",0);
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
    block=false;

    object->setProperty("animResizeEnable", true);
    object->setProperty("animMoveEnable", true);
    object->setProperty("visibilite", true);
    object->setProperty("taille", 424/taille-6);
    object->setProperty("opacity",1);
    merged=false;

    xAni= object->findChild<QObject*>("xAni");
    yAni= object->findChild<QObject*>("yAni");
    hAni= object->findChild<QObject*>("hAni");
    wAni= object->findChild<QObject*>("wAni");
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
bool BoxItem::getBlock(){
    return block;
}

void BoxItem::setBlock(bool bl){
    block=bl;
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
    if (!block)
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
    object->setProperty("size", 0);
}


bool BoxItem::getAnimRunning()
{
    if(hAni!=NULL && hAni->property("running").toBool()) return true;
    if(wAni!=NULL && wAni->property("running").toBool()) return true;
    if(xAni!=NULL && xAni->property("running").toBool()) return true;
    if(yAni!=NULL && yAni->property("running").toBool()) return true;
    return false;
}

