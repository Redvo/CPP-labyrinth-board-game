/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: gamewindow.h
 * Description: Header file for main game window.
 ***************************************************************************************/

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "gamemenu.h"

#include <game.h>

#include <QMainWindow>
#include <QLayoutItem>
#include <QLayout>
#include <QMatrix>
#include <QPixmap>
#include <QPushButton>
#include <QSignalMapper>
#include <QPainter>
#include <QLabel>
#include <QApplication>
#include <QDesktopWidget>
#include <QDir>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
    void CreateWindow();


private:
    Game *game;
    Ui::GameWindow *ui;
    void SetWindowSize();
    void Play();
    void RenderPack();
    void InitializeWindow();
    void ReleaseChildren(QObjectList children);
    void RenderHoldingCard();
    void RenderFreeStone();
    void RenderGameBoard();
    void RenderRotateButton();
    void RenderAchievedCards();
    void RenderEndTurnButton();
    void RenderPlayerPanel();
    void RenderArrowButtons();
    void RenderUndoButton();
    void RenderAchievedCard();

    QPixmap GetStoneImage(Stone *stone);

public slots:
    void close();
    void StartGame();
    void OpenGameMenu();
    void LoadGame();

private slots:
    void SaveGame();
    void RotateStone();
    void InsertStone(int x, int y);
    void MovePlayer(int x, int y);
    void ShowAchievedCards();
    void UndoAction();
    void EndTurn();
};

#endif // GAMEWINDOW_H
