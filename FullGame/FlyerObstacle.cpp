#include "BruinwalkMiniGame2.h"

/*
initializes the obstacle so that it enters from a random position in the
interval [0, SCREENWIDTH] pixels with FILENAME as its avatar firing at intervals
of .050 seconds
*/
FlyerObstacle::FlyerObstacle(QString filename): QObject(), QGraphicsPixmapItem(){
    // set random position
    const int SCREENWIDTH = 700;
    int random_number = rand() % SCREENWIDTH;
    setPos(random_number,0);

    // drew the rect
    setPixmap(QPixmap(filename));

    // connect
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);
}

/*/*
creates list of all flyer obstacles that are moving down and emits a signal when we
hit the player. this function also takes care of memory management when they exit the view
*/
void FlyerObstacle::move(){
        QList<QGraphicsItem *> colliding_items = collidingItems();
        for (int i = 0, n = colliding_items.size(); i < n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(Bruinwalk_Player)) {
                emit hit();
            }

    }
    // move obstacle down
    setPos(x(),y()+5);
    if (pos().y() + 30 < 0){
        scene()->removeItem(this);
        delete this;
    }

}
