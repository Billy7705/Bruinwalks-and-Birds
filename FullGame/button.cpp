#include "button.h"
#include <QGraphicsTextItem>
#include <QBrush>

/*
initializes the Button customizing its color and font size and text
while also allowing it to light up when we hover over it
*/
Button::Button(QString name, QGraphicsItem *parent): QGraphicsRectItem(parent){
    // draw the rect
    setRect(0,0,200,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);

    // draw the text
    text = new QGraphicsTextItem(name,this);
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);

    // allow responding to hover events
    setAcceptHoverEvents(true);
}

/*
signal for when the Button is clicked
*/
void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
}

/*
signal for when the mouse hovers over the Button making the
Button's colorbrighter
*/
void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    // change color to cyan
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    setBrush(brush);
}

/*
signal for when the mouse stops hovering over the Button
setting it back to its darker color
*/
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    // change color to dark cyan
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);
}
