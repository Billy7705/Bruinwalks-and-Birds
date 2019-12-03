#ifndef MYTIMER_H
#define MYTIMER_H
#include <QGraphicsTextItem>
#include <qlcdnumber.h>
#include <QTime>
#include <QTimer>
#include <QString>

/*
MY TIMER
class provides our custom timer to suite our MiniGame needs
    member fields
    @display        QGraphicsTextItem* to point where we want our countdown displayed
    @seconds_left   helps keep track of how much time has run out
*/
class MyTimer : public QLCDNumber
{
    Q_OBJECT

public:
    MyTimer(QGraphicsTextItem* display = 0, const int& seconds_left = 30);
    ~MyTimer()
    {
        delete display;
        display = nullptr;
    }

signals:
    void finish();
    void stop_timer();

public slots:
    void showTime();
    void stop_clock();

private:
    QGraphicsTextItem* display;
    int seconds_left;
};

#endif // MYTIMER_H
