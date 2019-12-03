#include "TrojanMiniGame1.h"
#include "button.h"
#include "mytimer.h"

/*
this initializes the mini_scene, the view, instructions/
description and the button to start the game
*/
TrojansMiniGame::TrojansMiniGame() {

    // create a scene
    mini_scene = new QGraphicsScene();

    // create a view to visualize the scene
    view = new QGraphicsView(mini_scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setStyleSheet("background: transparent");

    // show the view
    view->show();
    view->setFixedSize(800,600);
    mini_scene->setSceneRect(0,0,800,600);

    QGraphicsPixmapItem* pauly = new QGraphicsPixmapItem;
    pauly->setPixmap(QPixmap(":/pauly.png"));
    mini_scene->addItem(pauly);

    // create the title text
        QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("You’re sprinting outside Pauley looking up at the G.O.A.T John Wooden for inspiration when out of nowhere USC troublemakers come dashing towards you spray painting everything in sight. Jump over them to win time on your way to class. Press spacebar to flex that 6 foot Joe Bruin vertical and the left/right arrow keys to move across the screen."));
        QFont titleFont("comic sans",20);
        titleText->setDefaultTextColor(Qt::white);
        titleText->setFont(titleFont);
        titleText->setTextWidth(500);
        int txPos = this->width()/2 - titleText->boundingRect().width()/2;
        int tyPos = 50;
        titleText->setPos(txPos,tyPos);
        mini_scene->addItem(titleText);

        // create the play button
        Button* playButton = new Button(QString("Play"));
        int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
        int byPos = 500;
        playButton->setPos(bxPos,byPos);
        connect(playButton,SIGNAL(clicked()),this,SLOT(start_mini()));
        mini_scene->addItem(playButton);

        setWindowTitle("MiniGame");
}

/*
slot that starts the minigame and creates the timer, the player and all the obstacles
as well as connecting all objects to their respective signals/slots
*/
void TrojansMiniGame::start_mini() {

    mini_scene->clear();
    // create the backdrop to add to the scene
    QGraphicsPixmapItem* board = new QGraphicsPixmapItem;
    board->setPixmap(QPixmap(":/F_john.png"));
    mini_scene->addItem(board);

    Trojans_player* player = new Trojans_player();

    // add the player to the scene
    mini_scene->addItem(player);

    // make clock for the scene
    QGraphicsTextItem* clock = new QGraphicsTextItem(QString("30"));
    QFont titleFont("comic sans",50);
    clock->setFont(titleFont);
    int txPos = 200;
    int tyPos = 150;
    clock->setPos(txPos,tyPos);
    mini_scene->addItem(clock);

    MyTimer* countdown = new MyTimer(clock, 30);

    // make rect focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();


 player->setPos(50,550);

    // spawn obstacles so they're not so uniform
            QTimer * timer1 = new QTimer();
            QObject::connect(timer1,SIGNAL(timeout()),player,SLOT(create_obstacles()));
            timer1->start(3500);

            QTimer * timer2 = new QTimer();
            QObject::connect(timer2,SIGNAL(timeout()),player,SLOT(create_obstacles()));
            timer1->start(2000);

//            QTimer * timer3 = new QTimer();
//            QObject::connect(timer3,SIGNAL(timeout()),player,SLOT(create_obstacles()));
//            timer3->start(4000);

//            QTimer * timer4 = new QTimer();
//            QObject::connect(timer4,SIGNAL(timeout()),player,SLOT(create_obstacles()));
//            timer4->start(3000);

            clocks = {timer1, timer2};


    //ways to end game
    QObject::connect(player,SIGNAL(player_ended()),this,SLOT(lose_window()));

    QObject::connect(countdown,SIGNAL(finish()),this,SLOT(win_window()));

    QObject::connect(countdown,SIGNAL(finish()),player,SLOT(end()));

    QObject::connect(this,SIGNAL(stop_countdown()),countdown,SLOT(stop_clock()));

}

/*
this is the slot that disables the player in the background to win/lose
and announces that the player won the MiniGame while emitting the signal to the player
function to move the player to its respective spot. It also places a quit
button that closes the minigame window
*/
void TrojansMiniGame::win_window() {
    // disable all scene items

    emit win();

    for (QTimer* x : clocks)
    {
        x->stop();
      //  QObject::disconnect(x,SIGNAL(timeout()),player,SLOT(create_obstacles()));
//        delete x;
//        x = nullptr;
    }

    QGraphicsPixmapItem* board = new QGraphicsPixmapItem;
    board->setPixmap(QPixmap(":/F_football.png"));
    mini_scene->addItem(board);

    // create text annoucning winner
    QGraphicsTextItem* overText = new QGraphicsTextItem("You summoned your inner Joshua Kelly and powered your way through those pesky Trojans. You won precious minutes and delivered another L to USC.");
    overText->setPos(20,0);
    QFont overFont("comic sans",30);
    overText->setFont(overFont);
    overText->setDefaultTextColor(Qt::white);
    overText->setTextWidth(700);
    mini_scene->addItem(overText);


    Button* exit = new Button(QString("Return to Game"));
    int bxPos = this->width()/2 - exit->boundingRect().width()/2;
    int byPos = 400;
    exit->setPos(bxPos,byPos);
    connect(exit,SIGNAL(clicked()),this,SLOT(close()));
    mini_scene->addItem(exit);
}

/*
this is the slot that disables the player in the background to win/lose
and announces that the player lost the MiniGame while emitting the signal to the player
function to move the player to its respective spot. It also places a quit
button that closes the minigame window
*/
void TrojansMiniGame::lose_window() {
     //disable all scene items
    for (QTimer* x : clocks)
    {
        x->stop();
        QObject::disconnect(x,SIGNAL(timeout()),0,0);
    }

    emit stop_countdown();
    for (size_t i = 0, n = mini_scene->items().size(); i < n; i++){
        mini_scene->items()[i]->setEnabled(false);
    }

    QGraphicsPixmapItem* board = new QGraphicsPixmapItem;
    board->setPixmap(QPixmap(":/vandal.png"));
    mini_scene->addItem(board);

    // create text annoucning winner
    QGraphicsTextItem* overText = new QGraphicsTextItem("You got spray painted and had to stop to clean yourself. Guess you’re still stuck at Pauley.");
    overText->setPos(150,150);
    QFont overFont("comic sans",30);
    overText->setFont(overFont);
    overText->setDefaultTextColor(Qt::white);
    overText->setTextWidth(500);
    mini_scene->addItem(overText);

    Button* exit = new Button(QString("Return to Game"));
    int bxPos = this->width()/2 - exit->boundingRect().width()/2;
    int byPos = 400;
    exit->setPos(bxPos,byPos);
    connect(exit,SIGNAL(clicked()),this,SLOT(close()));
    mini_scene->addItem(exit);

}

/*
a slot to close the MiniGame window
*/
void TrojansMiniGame::close()
{
    view->close();
}

