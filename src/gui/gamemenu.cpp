/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: gamemenu.cpp
 * Description: Source code for game menu window.
 ***************************************************************************************/

#include "gamemenu.h"
#include "ui_gamemenu.h"

using namespace std;

GameMenu::GameMenu(Game **game, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameMenu)
{
    ui->setupUi(this);
    this->game = game;
    QObject::connect(this->ui->btn_startGame, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(this->ui->btn_startGame, SIGNAL(clicked()), parent, SLOT(StartGame()));
    QObject::connect(this->ui->btn_cancel, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(this->ui->btn_loadGame, SIGNAL(clicked(bool)), parent, SLOT(LoadGame()));
}

GameMenu::~GameMenu()
{
    delete ui;
}

void GameMenu::on_btn_startGame_clicked()
{
    this->numberOfPlayers = this->ui->sb_numberOfPlayers->text().toInt();
    this->boardSize = this->ui->sb_boardSize->text().toInt();
    this->numberOfCards = this->ui->sb_numberOfCards->text().toInt();
    *this->game = Game::NewGame(this->boardSize, this->numberOfCards, this->numberOfPlayers);
}

void GameMenu::on_btn_choseFile_clicked()
{
    this->fileName = QFileDialog::getOpenFileName(this,
        tr("Load saved game"), "./example/");
    if(!this->fileName.isEmpty()) {
        this->ui->te_filePath->setText(this->fileName);
    }
}

void GameMenu::on_btn_loadGame_clicked()
{
    if(this->ui->te_filePath->text().isEmpty()) {
        QMessageBox msgBox;
        msgBox.setText("Error: No file selected.");
        msgBox.setModal(true);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    } else {
        try {
            *this->game = Game::LoadGame(this->ui->te_filePath->text().toStdString());
        } catch(InvalidFileException *ex) {
            QMessageBox msgBox;
            msgBox.setText(QString::fromStdString(ex->GetMessage()));
            msgBox.setModal(true);
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
            return;
        }

        this->close();
    }
}

void GameMenu::on_btn_cancel_clicked()
{
    this->close();
}



