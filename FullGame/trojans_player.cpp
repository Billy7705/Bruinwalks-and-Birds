#include "TrojanMiniGame1.h"
#include <QObject>


/*
initializes Bruinwalk Player by setting its avatar and
connecting its signal to its move slote and stop slot
*/
Trojans_player::Trojans_player(): QObject(), QGraphicsPixmapItem(){

    setPixmap(QPixmap(":/F_bear.png"));

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    connect(this,SIGNAL(done()),timer,SLOT(stop()));

    timer->start(70);
}

/*
contains all the signals for when we move right and left and jump
*/
void Trojans_player::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Space){ //jump
        if (pos().y() == 550)
        setPos(x(),y()-300);
    }
    else if (event->key() == Qt::Key_Right){
        if (pos().x() + 10 < 1000)
        setPos(x()+30,y());
    }
    else if (event->key() == Qt::Key_Left){
        if (pos().x() > 0 )
        setPos(x()-30,y());
    }
}

/*
this sends out all the obstacles for the player to jump over
*/
void Trojans_player::create_obstacles(){
    // create an obstacle
    TrojanObstacle * trojan = new TrojanObstacle();
    scene()->addItem(trojan);
}

/*
this emits the signal when the player crashes
*/
void Trojans_player::move(){
    // if Player collides with obstacle, destroy both
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(TrojanObstacle))
            emit player_ended();
    }

    // move Player down
    if (pos().y() + 50 < 600)
        setPos(x(),y()+15);
}

/*
this moves the player out of the way of any incoming traffic in case
and sends a signal saying the game is done
*/
void Trojans_player::end() {
        setPos(x(),y()-300);
        emit done();

}
