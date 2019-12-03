#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>

/*
GAME
This is the wrapper class that controls all of our transitions, players,
and minigames dice rolls.
    @players        std::vector<Player*>containing all the players in the game
    @turn_count     integer value keeping track of how many turns have been played;
    @whosTurn_      QString object announcing the player to roll next
    @roll_int       stores the latest integer that was rolled on the dice
    @whosTurnText   QGraphicsTextItem pointer to announce who needs to roll dice
    @diceRolledText QGraphicsTextItem pointing to announce most recent play

*/

class Game: public QGraphicsView{
    Q_OBJECT
public:
    // constructors
    Game(QWidget* parent=NULL);
    ~Game() {
        for (Player* x : players)
        {
            delete x;
            x = nullptr;
        }
        delete whosTurnText;
        whosTurnText = nullptr;

    }

    // public methods
    void displayMainMenu();
    QString getWhosTurn() const;
    QString getDiceRollString() const;
    int getDiceRollInt() const;
    void setDiceRoll();
    void setWhosTurn();
    void displayGameOverWindow(QString name);
    void drawGUI();
    void check_multiplayer(Player* temp);


    QGraphicsScene* scene;

public slots:
    void displayPlayerNumber();
    void displayInstructions();
    void start();
    void move();
    void set_2_players();
    void set_3_players();
    void set_4_players();
    void send();


private:
    // private attributes
    std::vector<Player*> players;
    int turn_count;
    QString whosTurn_;
    int roll_int;
    QGraphicsTextItem* whosTurnText;
    QGraphicsTextItem* diceRolledText;

};


#endif // GAME_H
