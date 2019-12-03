#include "TrojanMiniGame1.h"
#include "BruinwalkMiniGame2.h"

/*
contructs TrojanObstacle object by letting it fire every 1/10 second and setting
it to be the tommy image
*/
TrojanObstacle::TrojanObstacle(): QObject(), QGraphicsPixmapItem(){
    //set random position
   // int random_number = rand() % 50;
    setPos(800,460);

    // drew the rect
    setPixmap(QPixmap(":/tommy.png"));

    // connect
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(100);
}


/*
creates list of all bird obstacles that are moving left. this function also
takes care of memory management when they exit the view
*/
void TrojanObstacle::move(){
    // move obstacle down
    setPos(x()-20,y());
    if (pos().x() + 80 < 0){
        scene()->removeItem(this);
        delete this;
    }
}


/*
creates list of all trojan obstacles that are moving left and emits a signal when we
hit the player. this function also takes care of memory management when they exit the view
*/
void TrojanObstacle::move_down(){
    // move obstacle down
    setPos(x(),y()+5);
    if (pos().y() + 140 < 0){
        scene()->removeItem(this);
        delete this;

        QList<QGraphicsItem *> colliding_items = collidingItems();
        for (int i = 0, n = colliding_items.size(); i < n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(Bruinwalk_Player)){
                // remove them both
//                scene()->removeItem(colliding_items[i]);
//                scene()->removeItem(this);
//                // delete them both
//                delete colliding_items[i];
//                delete this;
                emit strike();
                //return;
            }
    }
    }
}
