#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QString>
#include <QObject>
#include <QtWidgets>

/*
PLAYER
this class embodies our player pieces controlling how and where they move
accross the board and interact with each other
    member fields
    @index      integer keeping track which board piece player is on
    @saved_int  allows to keep track of dependent int when landing on snake/ladder
    @name       QString to display who's turn it is and other announcements
*/
class Player: public QObject, public QGraphicsRectItem{
    Q_OBJECT
private:
    int index;
    int saved_int;
    QString name;

public:
    // constructors
    Player();
    //~Player() {}
    void move_player(const int& roll);
    void check_snake();
    void check_ladder();
    int get_index() const;
    QString get_name() const;
    void set_name(const QString& new_name);
    virtual ~Player() {};
    void set_index(const int& n);
    std::vector<int> get_xy();


public slots:
    void set_win();
signals:
    void replace();

};


#endif // PLAYER_H
