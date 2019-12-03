#include <QApplication>
#include "game.h"

/*
PIC 10 C Final Project
by Billy and Sneha
12/7/2018


All images brought to you by the Daily Bruin
and images brought to you by playonloop.com

*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //creates and displays game
    Game* game = new Game();
    game->show();
    game->displayMainMenu();

    return a.exec();
}

