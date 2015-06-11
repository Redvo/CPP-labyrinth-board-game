/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: gamemenu.h
 * Description: Header file for game menu window.
 ***************************************************************************************/

#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <game.h>

#include <QDialog>
#include <QApplication>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QObject>

namespace Ui {
class GameMenu;
}

class GameMenu : public QDialog
{
    Q_OBJECT

public:
    explicit GameMenu(Game **game, QWidget *parent = 0);
    ~GameMenu();

private slots:
    void on_btn_startGame_clicked();

    void on_btn_choseFile_clicked();

    void on_btn_loadGame_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::GameMenu *ui;
    Game **game;
    QString fileName;
    int numberOfPlayers;
    int boardSize;
    int numberOfCards;

};

#endif // GAMEMENU_H
