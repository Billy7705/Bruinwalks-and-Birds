#ifndef BRUINWALK_H
#define BRUINWALK_H

//BRUINWALK MINIGAME
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QGraphicsScene>
//Further libraries needed for subclasses
#include <QList>
#include <stdlib.h>
#include <QKeyEvent>
#include <QString>
#include <QtWidgets>
#include <QPaintEvent>
#include <QGraphicsPixmapItem>
#include <QObject>

/*
BRUINWALK PLAYER
this class contains the player that the user controls and it also
contains the signals that direct the Bruinwalk MiniGame like shooting/moving
    member fields : none
*/
class Bruinwalk_Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Bruinwalk_Player(QGraphicsPixmapItem* parent = nullptr);
    ~Bruinwalk_Player() {}
    void keyPressEvent(QKeyEvent * event);

public slots:
        void create_obstacles();
        void hit2();

signals :
        void player_end();
};

/*
BRUINWALKMINIGAME
This class encompasses the broader scope of our Bruinwalk MiniGame and
orchestrates winning and losing and the set up and clean up of all objects
connected to it
    member variables
    @player     Bruinwalk_Player pointer to keep track of it and its children
    @miniscene  QGraphicsScene pointer to be able to add items to user's view
    @view       QGraphicsView pointer to keep track of closing the MiniGame window
*/
class BruinwalkMinigame: public QGraphicsView {
    Q_OBJECT
public:
    BruinwalkMinigame(QWidget* parent = 0);
    QGraphicsScene* mini_scene;
    ~BruinwalkMinigame() {
        delete player;
        delete view;
        player = nullptr;
        view = nullptr;
        mini_scene->clear();
        delete mini_scene;
        mini_scene= nullptr;
                         }

public slots :
    void start_mini();
    void win_window();
    void lose_window();
    void close();
signals:
    void win();
    void stop_countdown();

private:
    Bruinwalk_Player* player;
    QGraphicsView* view;
};

/*
BULLET
this is designed to construct the recycling bins that are thrown at flyers
to help dodge them
*/
class Bullet: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bullet();
public slots:
    void move();
};

/*
FLYER OBSTACLE
this class creates objects that can me shot down by bullets or avoided in
the Bruinwalk MiniGame
*/
class FlyerObstacle: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    FlyerObstacle(QString file_name = "");
public slots:
    void move();
signals:
    void hit();
};

/*
BIRD OBSTACLE
this creates the obstacle that cannot be shot down and must only be avoided
in the Bruinwalk MiniGame
*/
class BirdObstacle: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    BirdObstacle(const QString& filename = "");
public slots:
    void move_down();
signals:
    void strike();
private:
    const QString& filename;
};


#endif // BRUINWALK_H
