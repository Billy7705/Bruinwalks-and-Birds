#include "mytimer.h"

/*
initializes timer to tick every second and displayes it
*/
MyTimer::MyTimer(QGraphicsTextItem* display, const int& seconds_left)
    : display(display), seconds_left(seconds_left)
{
    //setSegmentStyle(Filled);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MyTimer::showTime);
    timer->start(1000);

    QObject::connect(this,SIGNAL(stop_timer()),timer,SLOT(stop()));

    showTime();
}

/*
displays time and ensures that time is always positive or zero
and when it is zero we emit the signal that we have finished the game
*/
void MyTimer::showTime()
{
    seconds_left--;
    if (seconds_left < 0) seconds_left = 0;
    if (seconds_left==0)
        emit finish();
    display->setPlainText(QString::number(seconds_left));
    display->setDefaultTextColor(Qt::white);
}

/*
this stops the internal timer to stop ticking
*/
void MyTimer::stop_clock() {
    emit stop_timer();
}
