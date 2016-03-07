#include "boxitem.h"

BoxItem::BoxItem(QObject *parent) : QObject(parent){
    boxValue="2";

    UpdateBox();
}
