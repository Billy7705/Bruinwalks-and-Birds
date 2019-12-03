#include "game.h"
#include "BruinwalkMiniGame2.h"
#include "TrojanMiniGame1.h"
#include <QPointF>
#include <QPolygonF>
#include <QVector>
#include <QBrush>
#include <QWidget>

/*
Set player to be a rectangle with a default position and name
*/
Player::Player() {
    setRect(0,0,20,20);
    setPos(45,470);
    index = 0;
    name = " ";
}

//accesor function of name
QString Player::get_name() const
{
    return name;
}

//mutator function of name
void Player::set_name(const QString& new_name)
{
    name = new_name;
}

//accessor of index
int Player::get_index() const {
    return index;
}

//mutator of index while updating the position on the board
void Player::set_index(const int& n) {
    index = n;
    std::vector<int> xy = get_xy();
    this->setPos(xy[0], xy[1]);

}

/*
calculates the xy pixel coordinates of the the player based on its index
    @return     an intvector with the coordinate pair in terms of pixels
*/
std::vector<int> Player::get_xy(){

    int tens = index/6;
    int ones = (index%6);
    int x,y;

    if (tens%2 == 0) { // pair
        x = 55 + 112*ones;
        y = 620 - 115*tens;
    }
    else {
        x = 612 - 112*ones;
        y = 616 - 115*tens;
    }

    return std::vector<int> {x,y};
}

/*this is the player helper function of the function Game::move()
this ensures that the player has to roll the exact number of spaces
in between them and the last to win as well as checks if they landed
on a special square
    @roll   int of what number they rolled on the dice
*/
void Player::move_player(const int& roll) {

    int temp = index;
    index += roll;
    if (index > 35)
    {index = temp;  //check that they don't fall off the board

    set_index(index);
    }

    check_snake();
    check_ladder();
}

/*
checks whether player landed on snake and automatically moves them down
while saving where they were previously so that if they win the MiniGame
they wont have to slide down the snake
*/
void Player::check_snake()
{
    if (index == 16)
    {
        saved_int = 16;
        set_index(3);
        TrojansMiniGame* b = new TrojansMiniGame();
        QObject::connect(b,SIGNAL(win()),this,SLOT(set_win()));
    }
    if (index == 19)
    {
        saved_int = 19;
        set_index(5);
        TrojansMiniGame* b = new TrojansMiniGame();
        QObject::connect(b,SIGNAL(win()),this,SLOT(set_win()));
    }
    if (index == 23)
    {
        saved_int = 23;
        set_index(15);
        TrojansMiniGame* b = new TrojansMiniGame();
        QObject::connect(b,SIGNAL(win()),this,SLOT(set_win()));
    }
    if (index == 33)
     {
        saved_int = 33;
        set_index(11);
        TrojansMiniGame* b = new TrojansMiniGame();
        QObject::connect(b,SIGNAL(win()),this,SLOT(set_win()));
    }
    if  (index == 31)
        {
        saved_int = 31;
        set_index(29);
        TrojansMiniGame* b = new TrojansMiniGame();
        QObject::connect(b,SIGNAL(win()),this,SLOT(set_win()));
    }
}

/*
checks whether player landed on ladder and does not automatically moves
them up but rather saving the potential promotion in saved_int
so that if they win the MiniGame they can move up the ladder
*/
void Player::check_ladder()
{

    if (index == 1) {
        saved_int = 14;
        BruinwalkMinigame* b = new BruinwalkMinigame();
        QObject::connect(b,SIGNAL(win()),this,SLOT(set_win()));
    }
    if (index == 4){
        saved_int = 6;
        BruinwalkMinigame* b = new BruinwalkMinigame();
        QObject::connect(b,SIGNAL(win()),this,SLOT(set_win()));
    }
    if (index == 8){
        saved_int = 26;
        BruinwalkMinigame* b = new BruinwalkMinigame();
        QObject::connect(b,SIGNAL(win()),this,SLOT(set_win()));
    }
    if (index == 17) {
        saved_int = 28;
        BruinwalkMinigame* b = new BruinwalkMinigame();
        QObject::connect(b,SIGNAL(win()),this,SLOT(set_win()));
    }
    if  (index == 24) {
        saved_int = 34;
        BruinwalkMinigame* b = new BruinwalkMinigame();
        QObject::connect(b,SIGNAL(win()),this,SLOT(set_win()));
    }
}

//emits signal saying we won to the Game object and updates the position accordingly
void Player::set_win() {
    set_index(saved_int);
    emit replace();
}
