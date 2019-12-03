#ifndef BIRD_H
#define BIRD_H

//BIRD MINIGAME
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
//BIRDPLAYER AND BLOCK
#include <QKeyEvent>
#include <QTimer>
#include <QList>
#include <stdlib.h>
#include <QGraphicsTextItem>
#include <QFont>
#include <QTimer>

/*
TROJANS PLAYER
this class contains the player that the user controls and more importantly
it contains the signals that direct the Trojans MiniGame like jumping
    member fields : none
*/
class Trojans_player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Trojans_player();
    void keyPressEvent(QKeyEvent * event);

public slots:
        void create_obstacles();
        void move();
        void end();
signals :
        void player_ended();
        void done();
};


/*
TROJANS MINIGAME
This class encompasses the broader scope of our Trojans MiniGame and
orchestrates winning and losing and the set up and clean up of all objects
connected to it
    member variables
    @player     Trojans_Player pointer to keep track of it and its children
    @miniscene  QGraphicsScene pointer to be able to add items to user's view
    @view       QGraphicsView pointer to keep track of closing the MiniGame window
    @clocks     vector of QTimer pointers to keep track during deallocation;
*/
class TrojansMiniGame: public QGraphicsView{
    Q_OBJECT
public:
    TrojansMiniGame();
    QGraphicsScene* mini_scene;
    ~TrojansMiniGame()
    {
        for(QTimer* x : clocks)
        {
            delete x;
            x = nullptr;
        }
        delete view;
        view = nullptr;
        mini_scene->clear();
        delete mini_scene;
        mini_scene = nullptr;
        delete player;
        player = nullptr;
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
    std::vector<QTimer*> clocks;
    Trojans_player* player;
    QGraphicsView * view;

};

/*
TROJAN OBSTACLE
this creates the obstacle that must only be jumped over in the Trojans MiniGame
*/
class TrojanObstacle: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    TrojanObstacle();
public slots:
    void move();
    void move_down();
signals:
    void strike();
};

#endif // BIRD_H
