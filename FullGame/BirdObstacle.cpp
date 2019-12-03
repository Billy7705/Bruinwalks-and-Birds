#include "BruinwalkMiniGame2.h"


/*
contructs BirdObstacle object by letting it move at a rate of SPEED and in the window
of 0 pixels to SCREENWIDTH with image from FILENAME
*/
BirdObstacle::BirdObstacle(const QString& filename)
    : QObject(), QGraphicsPixmapItem(), filename(filename) {
    //set random position
    const int SCREENWIDTH = 700;
    const int SPEED = 150;
    int random_number = rand() % SCREENWIDTH;
    setPos(random_number,0);

    // drew the rect
    setPixmap(QPixmap(filename));


    // connect
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move_down()));

    timer->start(SPEED);
}

/*
creates list of all bird obstacles that are moving down and emits a signal when we
hit the player. this function also takes care of memory management when they exit the view
*/
void BirdObstacle::move_down(){
        QList<QGraphicsItem *> colliding_items = collidingItems();
        for (int i = 0, n = colliding_items.size(); i < n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(Bruinwalk_Player))
                emit strike();
    }
        // move obstacle down
        setPos(x(),y()+5);
        if (pos().y() + 140 < 0){
            scene()->removeItem(this);
            delete this;
    }
}
