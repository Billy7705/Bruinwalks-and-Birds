#include "BruinwalkMiniGame2.h"

/*
initializes Bruinwalk Player by setting its avatar
*/
Bruinwalk_Player::Bruinwalk_Player(QGraphicsPixmapItem *parent){
    setPixmap(QPixmap(":/F_bear.png"));
}

/*
contains all the signals for when we move right and left and shoot
*/
void Bruinwalk_Player::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Left){
        if (pos().x() > 0)
        setPos(x()-30,y());
    }
    else if (event->key() == Qt::Key_Right){
        if (pos().x() + 100 < 800)
        setPos(x()+30,y());
    }
    else if (event->key() == Qt::Key_Space){
        // create a bullet
        Bullet * bullet = new Bullet();
        bullet->setPos(x(),y());
        scene()->addItem(bullet);
    }
}
/*
this sends out all the obstacles for the player to dodge and shoot
we create 3 types of flyers and two types of scooters - a lime and a bird
as well as connecting them to their respective slot
*/
void Bruinwalk_Player::create_obstacles(){
    // create an flyer
    FlyerObstacle * flyer = new FlyerObstacle(":/flyer.jpg");
    scene()->addItem(flyer);

    FlyerObstacle * flyer2 = new FlyerObstacle(":/flyer2.jpg");
    scene()->addItem(flyer2);

    FlyerObstacle * flyer3 = new FlyerObstacle(":/flyer3.jpg");
    scene()->addItem(flyer3);

    BirdObstacle * bird = new BirdObstacle(":/F_bird.png");
    scene()->addItem(bird);
    BirdObstacle * lime = new BirdObstacle(":/F_lime.png");
    scene()->addItem(lime);

    QObject::connect(flyer,SIGNAL(hit()), this, SLOT(hit2()));
    QObject::connect(flyer2,SIGNAL(hit()), this, SLOT(hit2()));
    QObject::connect(flyer3,SIGNAL(hit()), this, SLOT(hit2()));
    QObject::connect(bird,SIGNAL(strike()), this, SLOT(hit2()));
    QObject::connect(lime,SIGNAL(strike()), this, SLOT(hit2()));

}

/*
slot announcing the player has been hit and that they lost
*/
void Bruinwalk_Player::hit2() {
    setPos(850,y());
    emit player_end();
}


