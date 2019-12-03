#include "BruinwalkMiniGame2.h"
#include "button.h"
#include "mytimer.h"

/*
this initializes the mini_scene and the view and
*/
BruinwalkMinigame::BruinwalkMinigame(QWidget *parent){

    // create a scene
    mini_scene = new QGraphicsScene();
    mini_scene->setSceneRect(0,0,880,600);


    // create a view to visualize the scene
    view = new QGraphicsView(mini_scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setStyleSheet("background: transparent");

    // show the view
    view->show();
    view->setFixedSize(800,600);
    mini_scene->setSceneRect(0,0,800,600);

    //backdrop
    QGraphicsPixmapItem* board = new QGraphicsPixmapItem;
    board->setPixmap(QPixmap(":/F_bwalk.png"));
    mini_scene->addItem(board);

    // create the title text
        QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("BruinWalk is the busiest you’ve ever seen it, the line to the engineering fair seems to have flooded the path to class as students struggle to find room to sell their succulents and Bird scooters come dashing at you uncontrollably. Press the left/right arrow keys to avoid getting hit by oncoming objects, you can also shoot down flyers (but not birds) by pressing spacebar. "));
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
        int bxPos = this->width()/2 - playButton->boundingRect().width()/2;;
        int byPos = 500;
        playButton->setPos(bxPos,byPos);
        connect(playButton,SIGNAL(clicked()),this,SLOT(start_mini()));
        mini_scene->addItem(playButton);

        setWindowTitle("MiniGame");
}

void BruinwalkMinigame::start_mini() {

    mini_scene->clear();
    QGraphicsPixmapItem* board = new QGraphicsPixmapItem;
    board->setPixmap(QPixmap(":/F_bruinwalk.png"));
    mini_scene->addItem(board);

    // create an item to add to the scene
    player = new Bruinwalk_Player();

    // add the item to the scene
    mini_scene->addItem(player);

    QGraphicsTextItem* clock = new QGraphicsTextItem("30");
    QFont titleFont("comic sans",50);
    clock->setFont(titleFont);
    int txPos = 200;
    int tyPos = 150;
    clock->setPos(txPos,tyPos);
    mini_scene->addItem(clock);

    MyTimer* countdown = new MyTimer(clock, 25);

    // make rect focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();


    player->setPos(400,550);

    // spawn obstacles
        QTimer * timer = new QTimer();
        QObject::connect(timer,SIGNAL(timeout()),player,SLOT(create_obstacles()));
        QObject::connect(player,SIGNAL(player_end()),timer,SLOT(stop()));
        QObject::connect(countdown,SIGNAL(finish()),timer,SLOT(stop()));


        timer->start(2000);

    QObject::connect(player,SIGNAL(player_end()),this,SLOT(lose_window()));

    QObject::connect(countdown,SIGNAL(finish()),this,SLOT(win_window()));

    QObject::connect(this,SIGNAL(stop_countdown()),countdown,SLOT(stop_clock()));



}

/*
this is the slot that disables the player in the background to win/lose
and announces that the player won the MiniGame while emitting the signal to the player
function to move the player to its respective spot. It also places a quit
button that closes the minigame window
*/
void BruinwalkMinigame::win_window() {
    // disable all scene items
    QObject::disconnect(player,SIGNAL(player_end()),nullptr,nullptr);

    emit win();

    for (size_t i = 0, n = mini_scene->items().size(); i < n; i++){
        mini_scene->items()[i]->setEnabled(false);
    }


    QGraphicsPixmapItem* board = new QGraphicsPixmapItem;
    board->setPixmap(QPixmap(":/F_pedestrian.png"));
    mini_scene->addItem(board);

    // create text annoucning winner
    QGraphicsTextItem* overText = new QGraphicsTextItem("You soared through the sea of Birds unfettered and didn’t lose any time on your way to class!");
    overText->setPos(0,100);
    QFont overFont("comic sans",30);
    overText->setFont(overFont);
    overText->setDefaultTextColor(Qt::white);
    overText->setTextWidth(300);
    mini_scene->addItem(overText);

    Button* exit = new Button(QString("Return to Game"));
    int bxPos = this->width()/2 - exit->boundingRect().width()/2;
    int byPos = 500;
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
void BruinwalkMinigame::lose_window() {
    // disable all scene items

    emit stop_countdown();
    for (size_t i = 0, n = mini_scene->items().size(); i < n; i++){
        mini_scene->items()[i]->setEnabled(false);
    }

    QGraphicsPixmapItem* board = new QGraphicsPixmapItem;
    board->setPixmap(QPixmap(":/F_broken.png"));
    mini_scene->addItem(board);

    // create text annoucning winner
    QGraphicsTextItem* overText = new QGraphicsTextItem("You stopped to pick up a flyer and got struck by a bird in flight, losing several minutes. You’re chances of making it to class are slowly falling apart like the bird that hit you.");
    overText->setPos(40,20);
    QFont overFont("comic sans",30);
    overText->setFont(overFont);
   // overText->setDefaultTextColor(Qt::darkCyan);
    overText->setTextWidth(500);
    mini_scene->addItem(overText);

    Button* exit = new Button(QString("Return to Game"));
    int bxPos = this->width()/2 - exit->boundingRect().width()/2;
    int byPos = 500;
    exit->setPos(bxPos,byPos);
    connect(exit,SIGNAL(clicked()),this,SLOT(close()));
    mini_scene->addItem(exit);
}

/*
a slot to close the MiniGame window
*/
void BruinwalkMinigame::close()
{
    view->close();
}
