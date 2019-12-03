#include "BruinwalkMiniGame2.h"

/*
this sets the avatar of the bullet ot be the recycling can
and starts the timer in which it will move to
*/
Bullet::Bullet(): QObject(), QGraphicsPixmapItem(){
    // drew the rect
    setPixmap(QPixmap(":/F_recycle.png"));

    // connect
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);
}

/*
this takes care of moving the bullet after it has been fired
as well as removing all FlyerObstacles that are in its
trajectory and once it reaches the end it will delete itslef
*/
void Bullet::move(){
    // if bullet collides with obstacle, destroy both
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(FlyerObstacle)){
            // remove them both
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            // delete them both
            delete colliding_items[i];
            delete this;
            return;
        }
    }

    QList<QGraphicsItem *> colliding_items2 = collidingItems();
    for (int i = 0, n = colliding_items2.size(); i < n; ++i){
        if (typeid(*(colliding_items2[i])) == typeid(BirdObstacle)){
            // remove them both
            scene()->removeItem(this);
            // delete them both
            delete this;
            return;
        }
    }

    // move bullet up
    setPos(x(),y()-10);
    if (pos().y() + 20 < 0){
        scene()->removeItem(this);
        delete this;
    }
}
