#include "game.h"
#include "button.h"
#include <QGraphicsTextItem>
#include <stdlib.h> // srand() and rand()
#include <time.h> // time()
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QMediaPlayer>
#include <QMediaPlaylist>

/*
initializes board by setting up the window and Qgraphicsscene
*/
Game::Game(QWidget *parent) : turn_count(0) {
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1300,700);

    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1300,700);
    setScene(scene);

    setWindowTitle("Bruinwalks and Birds");

}

/*
this creates the first screen users will see when opening the game
*/
void Game::displayMainMenu(){
    // create the title text
    QGraphicsPixmapItem* board = new QGraphicsPixmapItem;
    board->setPixmap(QPixmap(":/F_plaza.png"));
    scene->addItem(board);

    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Welcome to Bruinwalks and Birds!"));
    QFont titleFont("lucida grande",40);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 100;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the play button
    Button* playButton = new Button(QString("Play"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 225;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(displayInstructions()));
    scene->addItem(playButton);

    // create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 300;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);

    QMediaPlaylist * playlist = new QMediaPlaylist();
        playlist->addMedia(QUrl("qrc:/music.wav"));
        playlist->setPlaybackMode(QMediaPlaylist::Loop);

        QMediaPlayer * music = new QMediaPlayer;
        music->setPlaylist(playlist);
        music->play();

        Button* mute = new Button(QString("Mute"));
        int x = this->width()/2 - quitButton->boundingRect().width()/2;
        int y = 375;
        mute->setPos(x,y);
        connect(mute,SIGNAL(clicked()),music,SLOT(stop()));
        scene->addItem(mute);

}

/*
this creates the second screen users will see when opening the game
while displaying instructions
*/
void Game::displayInstructions() {

    scene->clear();

    QGraphicsPixmapItem* board = new QGraphicsPixmapItem;
    board->setPixmap(QPixmap(":/F_hill.png"));
    scene->addItem(board);

    // create the title text
    QGraphicsTextItem* instructions = new QGraphicsTextItem(QString("Oh No! You were up all night studying for your midterm and missed you’re alarm! You only have a few minutes to Boelt(er) all the way to class so you don’t fail your exam. Roll the dice to advance through campus, but make sure to watch out for obstacles along the way! "));
    QFont insFont("comic sans",30);
    instructions->setDefaultTextColor(Qt::white);
    instructions->setTextWidth(700);
    instructions->setFont(insFont);
    int txPos = this->width()/2 - instructions->boundingRect().width()/2;
    int tyPos = 100;
    instructions->setPos(txPos,tyPos);
    scene->addItem(instructions);

    //creates next button to go to next screen
    Button* nextButton = new Button(QString("Next"));
    int bxPos = this->width()/2 - nextButton->boundingRect().width()/2;
    int byPos = this->height()*.75;
    nextButton->setPos(bxPos,byPos);
    connect(nextButton,SIGNAL(clicked()),this,SLOT(displayPlayerNumber()));
    scene->addItem(nextButton);
}

/*
this creates the third screen users will see when opening the game
allowing them to choose number of players
*/
void Game::displayPlayerNumber(){
    // create the title text
    scene->clear();

    QGraphicsPixmapItem* board = new QGraphicsPixmapItem;
    board->setPixmap(QPixmap(":/F_won.png"));
    scene->addItem(board);

    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Select Number of Bruins"));
    titleText->setDefaultTextColor(Qt::white);
    QFont titleFont("comic sans",40);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 100;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create 2 player button
    Button* player2 = new Button(QString("2 Players"));
    int bxPos = this->width()/2 - player2->boundingRect().width()/2;
    int byPos = 200;
    player2->setPos(bxPos,byPos);
    connect(player2,SIGNAL(clicked()),this,SLOT(set_2_players()));
    scene->addItem(player2);

    // create 3 player button
    Button* player3 = new Button(QString("3 Players"));
    int qxPos3 = this->width()/2 - player3->boundingRect().width()/2;
    int qyPos3 = 300;
    player3->setPos(qxPos3,qyPos3);
    connect(player3,SIGNAL(clicked()),this,SLOT(set_3_players()));
    scene->addItem(player3);

    // create 4 player button
    Button* player4 = new Button(QString("4 Players"));
    int qxPos4 = this->width()/2 - player4->boundingRect().width()/2;
    int qyPos4 = 400;
    player4->setPos(qxPos4,qyPos4);
    connect(player4,SIGNAL(clicked()),this,SLOT(set_4_players()));
    scene->addItem(player4);
}

//initializes two player pointers and stores them in players vector
void Game::set_2_players() {
    players.push_back(new Player());
    players[0]->setBrush(Qt::red);
    players[0]->set_name("Player 1");
    players[0]->setPos(26,594);

    players.push_back(new Player());
    players[1]->setBrush(Qt::blue);
    players[1]->set_name("Player 2");
    players[1]->setPos(79,646);

    start();
}

//initializes three player pointers and stores them in players vector
void Game::set_3_players() {
    players.push_back(new Player());
    players[0]->setBrush(Qt::red);
    players[0]->set_name("Player 1");
    players[0]->setPos(26,594);


    players.push_back(new Player());
    players[1]->set_name("Player 2");
    players[1]->setBrush(Qt::blue);
    players[1]->setPos(79,646);


    players.push_back(new Player());
    players[2]->setBrush(Qt::green);
    players[2]->set_name("Player 3");
    players[2]->setPos(79,594);


    start();
}

//initializes two player pointers and stores them in players vector
void Game::set_4_players() {
    players.push_back(new Player());
    players[0]->setBrush(Qt::red);
    players[0]->set_name("Player 1");
    players[0]->setPos(26,594);


    players.push_back(new Player());
    players[1]->set_name("Player 2");
    players[1]->setBrush(Qt::blue);
    players[1]->setPos(79,646);


    players.push_back(new Player());
    players[2]->setBrush(Qt::green);
    players[2]->set_name("Player 3");
    players[2]->setPos(79,594);


    players.push_back(new Player());
    players[3]->setBrush(Qt::yellow);
    players[3]->set_name("Player 4");
    players[3]->setPos(26,646);


    start();
}

/*
this is our function to set up the game board and initialize
*/
void Game::start(){

    // clear the screen
    scene->clear();
    drawGUI();
    for (size_t i = 0; i < players.size(); i++)
        scene->addItem(players[i]);
}

/*
this adds all of the items on screen and updates the screen
*/
void Game::drawGUI(){
    QGraphicsPixmapItem* board = new QGraphicsPixmapItem;
    board->setPixmap(QPixmap(":/F_Snakes.jpg"));
    scene->addItem(board);

    // place player turn text
    whosTurnText = new QGraphicsTextItem();
    QFont turnFont("comic sans",20);
    whosTurnText->setTextWidth(250);
    whosTurnText->setFont(turnFont);
    setWhosTurn();
    whosTurnText->setPos(860,250);
    scene->addItem(whosTurnText);

    // place dice roll text
    diceRolledText = new QGraphicsTextItem();
    QFont diceFont("comic sans",20);
    diceRolledText->setFont(diceFont);
    diceRolledText->setTextWidth(250);
    diceRolledText->setPlainText(QString(" "));
    diceRolledText->setPos(860,50);
    scene->addItem(diceRolledText);

    Button* DiceRollButton = new Button(QString("Press to Roll Dice"));
    int dxPos = 860;
    int dyPos = 400;
    DiceRollButton->setPos(dxPos,dyPos);
    connect(DiceRollButton,SIGNAL(clicked()),this,SLOT(move()));
    scene->addItem(DiceRollButton);


}

//retriever for name of the person of who's turn it is
QString Game::getWhosTurn() const {
    return whosTurn_;
}

//retreiver of the lates number rolled
int Game::getDiceRollInt() const {
    return roll_int;
}

//updates to the next player while announcing previous events
void Game::setWhosTurn(){
    int turn = turn_count%players.size();
    whosTurn_ = players[turn]->get_name();

    // change the QGraphicsTextItem
    QString dialog = ": it's your turn to roll the Dice. ";

    int index = players[turn]->get_index();
    if (index == 34)
    {
        dialog = dialog + "\nRoll a 1 to win!";
    }
    else if(index > 29)
    {
        QString maxroll = QString::number(35-index);
        dialog = dialog + "\nRoll a " + maxroll + " or less to move.";
    }
    whosTurnText->setPlainText(QString(players[turn]->get_name() + dialog));
}

//generates random number that mimics a dice roll and announces to the screen
void Game::setDiceRoll(){
    srand (time(NULL));
    roll_int = rand()%6+1;
    int turn = turn_count%players.size();
    diceRolledText->setPlainText(QString(players[turn]->get_name() +" rolled a: " + QString::number(roll_int)));
}

/*
this checks if there are two players in box and if so updates the board so that
both pieces can be seen without one blocking the other
*/
void Game::check_multiplayer(Player* temp) {

    std::vector<Player*> samebox; //players with same index
    for (size_t i = 0; i < players.size(); i++) {
        if(players[i]->get_index() == temp->get_index())
            samebox.push_back(players[i]);
    }

    if(samebox.size() > 1)
    {
        std::vector<int> xy = samebox[1]->get_xy();
        samebox[0]->setPos(xy[0]-20, xy[1]-20);
        samebox[1]->setPos(xy[0]+20, xy[1]+20);
        if (samebox.size() > 2)
        {
            samebox[2]->setPos(xy[0]-20, xy[1]+20);
            if (samebox.size() > 3)
            {
                samebox[3]->setPos(xy[0]+20, xy[1]-20);
            }
        }
    }
}

/*
slot to react to when the dice is rolled
*/
void Game::move(){

    //roll dice
    setDiceRoll();
    Player* temp = players[turn_count%players.size()];
    temp->move_player(roll_int);    //update player position

    //get and set coordinates in terms of pixels for the board
    std::vector<int> xy = temp->get_xy();
    temp->setPos(xy[0], xy[1]);

    //check if they have reached the end
    if (temp->get_index() == 35){
        displayGameOverWindow(temp->get_name());
    }

    //update the turn and display
    turn_count++;
    setWhosTurn();

    //when we do move them we must update the board
    QObject::connect(temp,SIGNAL(replace()),this,SLOT(send()));
    check_multiplayer(temp);
}

/*
slot for when we win or lose minigame to move the player into the right spot
*/
void Game::send() {

    Player* temp = players[(turn_count-1)%players.size()];
    int ind = temp->get_index();
    temp->set_index(ind);
    check_multiplayer(temp);
//    int tens = ind/6;
//    int ones = (ind%6);

//    if (tens%2 == 0) // pair
//         players[(turn_count-1)%players.size()]->setPos(40 + 85*ones, 480-85*tens);
//    else
//        players[(turn_count-1)%players.size()]->setPos(465 - 85*ones, 480-85*tens);
}

/*
when a player reaches index 35 (the last tile) then we announce the winner
*/
void Game::displayGameOverWindow(QString name){

        QGraphicsPixmapItem* back = new QGraphicsPixmapItem;
        back->setPixmap(QPixmap(":/logo1.png"));
        scene->addItem(back);

    // create playAgain button
//    Button* playAgain = new Button(QString("Play Again"));
//    playAgain->setPos(410,300);
//    scene->addItem(playAgain);
//    connect(playAgain,SIGNAL(clicked()),this,SLOT(restartGame()));

    // create quit button
    Button* quit = new Button(QString("Quit"));
    quit->setPos(500,455);
    scene->addItem(quit);
    connect(quit,SIGNAL(clicked()),this,SLOT(close()));

    // create text annoucning winner
    QGraphicsTextItem* overText = new QGraphicsTextItem(QString(name + " Congrats you made it to class on time and aced your midterm! You are the one true Bruin!"));
    overText->setPos(200,25);
    QFont endFont("comic sans",50);
    overText->setFont(endFont);
    overText->setDefaultTextColor(Qt::white);
    overText->setTextWidth(600);
    scene->addItem(overText);

}
