/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: main.cpp
 * Description: Main file of GUI based Labyrinth board game.
 ***************************************************************************************/

#include "gamewindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QStyle>
#include <QResource>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QResource::registerResource("./src/gui/images.rcc");
    GameWindow w;
    w.CreateWindow();
    w.show();
    w.OpenGameMenu();

    return a.exec();
}
