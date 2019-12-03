#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

/*
BUTTON

This class allowed us to customize our own button that lights up when
hovered over.
    member fields
    @text   QGraphicsTextItem pointer to the words we want displayed in
            the button itself
*/
class Button : public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    // constructors
    Button(QString name, QGraphicsItem* parent=NULL);
    ~Button() { delete text; text = nullptr; }
    // public methods (events)
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    void clicked();
private:
    QGraphicsTextItem* text;
};

#endif // BUTTON_H
