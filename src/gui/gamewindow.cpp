/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: gamewindow.cpp
 * Description: Source code for main game window.
 ***************************************************************************************/

#include "gamewindow.h"
#include "ui_gamewindow.h"

using namespace std;

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    this->game = NULL;
    QObject::connect(this->ui->mainMenu_newGame,SIGNAL(triggered()), this, SLOT(OpenGameMenu()));
    QObject::connect(this->ui->mainMenu_saveGame,SIGNAL(triggered()), this, SLOT(SaveGame()));
}

GameWindow::~GameWindow()
{
    delete ui;
    delete this->game;
    this->ReleaseChildren(this->centralWidget()->children());
}

void GameWindow::OpenGameMenu() {
    GameMenu *gm = new GameMenu(&this->game, this);
    gm->setFixedSize(250, 425);
    gm->setModal(true);
    gm->show();
}

void GameWindow::close() {
    this->close();
}

/*************************************************
 * Functions
 */

void GameWindow::StartGame() {

    if(this->game == NULL) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Game could not start.");
        msgBox.setModal(true);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    if(this->game->GetCurrentPlayer()->GetTreasureCard() == NULL) {
        this->game->GetCurrentPlayer()->SetTreasureCard(game->PopCard());
    }

    this->SetWindowSize();
    this->RenderRotateButton();
    this->RenderFreeStone();
    this->RenderUndoButton();
    this->RenderAchievedCard();
    this->RenderEndTurnButton();
    this->RenderPlayerPanel();
    this->RenderArrowButtons();
    this->RenderGameBoard();

}

QPixmap GameWindow::GetStoneImage(Stone *stone) {
    QPixmap bkgnd;
    QMatrix rm;

    switch(stone->GetStoneType()) {
        case StoneType::_ST_L: {
            bkgnd = QPixmap(":/images/stones/Stone_L");
            switch(stone->GetRotationType()) {
                case StoneRotation::_SR_T: {
                    rm.rotate(0);
                } break;
                case StoneRotation::_SR_L: {
                    rm.rotate(270);
                } break;
                case StoneRotation::_SR_B: {
                    rm.rotate(180);
                } break;
                case StoneRotation::_SR_R: {
                    rm.rotate(90);
                } break;
            }
        } break;
        case  StoneType::_ST_T: {
            bkgnd = QPixmap(":/images/stones/Stone_T");
            switch(stone->GetRotationType()) {
                case StoneRotation::_SR_T: {
                    rm.rotate(0);
                } break;
                case StoneRotation::_SR_L: {
                    rm.rotate(270);
                } break;
                case StoneRotation::_SR_B: {
                    rm.rotate(180);
                } break;
                case StoneRotation::_SR_R: {
                    rm.rotate(90);
                } break;
            }
        } break;
        case StoneType::_ST_I: {
            bkgnd = QPixmap(":/images/stones/Stone_I");
            switch(stone->GetRotationType()) {
                case StoneRotation::_SR_T:
                case StoneRotation::_SR_B:{
                    rm.rotate(0);
                } break;
                case StoneRotation::_SR_L:
                case StoneRotation::_SR_R:{
                    rm.rotate(90);
                } break;
            }
        } break;
    }

    bkgnd = bkgnd.transformed(rm);
    return bkgnd;

}


/****************************************
 * Initialization
 */


void GameWindow::SetWindowSize() {
    this->ReleaseChildren(this->centralWidget()->children());
    int width, height;
    width = 500 + (game->GetBoardSize() * 72);
    height = 200 + (game->GetBoardSize() * 72);
    this->setFixedSize(width, height);
    this->centralWidget()->setAutoFillBackground(false);
}

void GameWindow::ReleaseChildren(QObjectList children) {
    for(auto child : children) {
        this->ReleaseChildren(child->children());
        delete child;
    }
}

void GameWindow::CreateWindow() {
    this->ReleaseChildren(this->centralWidget()->children());
    this->setFixedSize(512,512);
    QPixmap pixmap = QPixmap(":/images/backgrounds/TitleBG");
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this->centralWidget()->setAutoFillBackground(true);
    this->centralWidget()->setPalette(palette);
    this->setGeometry(
        QStyle::alignedRect(
        Qt::LeftToRight,
        Qt::AlignCenter,
        this->size(),
        QApplication::desktop()->availableGeometry()
    ));
}

/***********************************
 * RENDERING
 */

void GameWindow::RenderRotateButton() {
    QPushButton *rotateButton = new QPushButton(this->centralWidget());
    rotateButton->setGeometry(30,90,72,72);
    rotateButton->setFlat(true);
    rotateButton->setIcon(QIcon(":/images/buttons/Rotate"));
    rotateButton->setIconSize(QSize(72,72));
    rotateButton->setAutoFillBackground(true);
    rotateButton->setStyleSheet("QPushButton{background: transparent;}");
    rotateButton->show();
    QObject::connect(rotateButton, SIGNAL(clicked(bool)), this, SLOT(RotateStone()));
}

void GameWindow::RenderFreeStone() {
    QPixmap pixmap = GetStoneImage(this->game->GetFreeStone());
    QWidget *freeStone = new QWidget(this->centralWidget());
    freeStone->setGeometry(122,90,72,72);
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    freeStone->setAutoFillBackground(true);
    freeStone->setPalette(palette);
    freeStone->show();
}

void GameWindow::RenderUndoButton() {
    QPushButton *undoButton = new QPushButton(this->centralWidget());
    undoButton->setGeometry(30,182,72,72);
    undoButton->setFlat(true);
    undoButton->setIcon(QIcon(":/images/buttons/Undo"));
    undoButton->setIconSize(QSize(72,72));
    undoButton->setAutoFillBackground(true);
    undoButton->setStyleSheet("QPushButton{background: transparent;}");
    undoButton->show();
    QObject::connect(undoButton, SIGNAL(clicked(bool)), this, SLOT(UndoAction()));
}

void GameWindow::RenderAchievedCard() {
    QPushButton *achievedCardsButton = new QPushButton(this->centralWidget());
    achievedCardsButton->setGeometry(122,182,72,72);
    achievedCardsButton->setFlat(true);
    achievedCardsButton->setIcon(QIcon(":/images/cards/CardPack"));
    achievedCardsButton->setIconSize(QSize(72,72));
    achievedCardsButton->setAutoFillBackground(true);
    achievedCardsButton->setStyleSheet("QPushButton{background: transparent;}");
    achievedCardsButton->show();
    QObject::connect(achievedCardsButton, SIGNAL(clicked(bool)), this, SLOT(ShowAchievedCards()));
}

void GameWindow::RenderEndTurnButton() {
    QPushButton *endTurnButton = new QPushButton(this->centralWidget());
    endTurnButton->setGeometry(214,182,72,72);
    endTurnButton->setFlat(true);
    endTurnButton->setIcon(QIcon(":/images/buttons/Next"));
    endTurnButton->setIconSize(QSize(72,72));
    endTurnButton->setAutoFillBackground(true);
    endTurnButton->setStyleSheet("QPushButton{background: transparent;}");
    endTurnButton->show();
    QObject::connect(endTurnButton, SIGNAL(clicked(bool)), this, SLOT(EndTurn()));
}

void GameWindow::RenderPlayerPanel() {

    for(auto player : this->game->GetPlayerList()) {

        QRect rectPlayer, rectCard;

        switch(player->GetPlayerId()) {
            case 1: {
                rectPlayer = QRect(50,320,50,50);
                rectCard = QRect(110,300,72,90);
            } break;
            case 2: {
                rectPlayer = QRect(50,420,50,50);
                rectCard = QRect(110,400,72,90);
            } break;
            case 3: {
                rectPlayer = QRect(200,320,50,50);
                rectCard = QRect(250,300,72,90);
            } break;
            case 4:
            default: {
                rectPlayer = QRect(200,420,50,50);
                rectCard = QRect(250,400,72,90);
            } break;

        }

        QString res = ":/images/players/Player" +
                QString::number(player->GetPlayerId());
        QPixmap pixmap(res);
        QWidget *playerIcon = new QWidget(this->centralWidget());
        playerIcon->setGeometry(rectPlayer);
        QPalette palette;
        palette.setBrush(QPalette::Background,QBrush(pixmap));
        playerIcon->setAutoFillBackground(true);
        playerIcon->setPalette(palette);
        playerIcon->show();

        if(player == this->game->GetCurrentPlayer()) {
            QPixmap *pixmap = new QPixmap(72, 90);
            pixmap->fill(Qt::transparent);
            QPainter *painter=new QPainter(pixmap);
            painter->drawPixmap(0, 0, 72, 90, QPixmap(":/images/cards/CardVisible"));

            if(player->GetTreasureCard() != NULL) {
                QString res = ":/images/items/Item" +
                        QString::number(player->GetTreasureCard()->GetCardNumber());
                QPixmap item(res);
                painter->drawPixmap(11,20,50,50,item);
            }

            QWidget *playerIcon = new QWidget(this->centralWidget());
            playerIcon->setGeometry(rectCard);
            QPalette palette;
            palette.setBrush(QPalette::Background,QBrush(*pixmap));
            playerIcon->setAutoFillBackground(true);
            playerIcon->setPalette(palette);
            playerIcon->show();
        } else {
            QPixmap pixmap(":/images/cards/CardHidden");
            QWidget *playerIcon = new QWidget(this->centralWidget());
            playerIcon->setGeometry(rectCard);
            QPalette palette;
            palette.setBrush(QPalette::Background,QBrush(pixmap));
            playerIcon->setAutoFillBackground(true);
            playerIcon->setPalette(palette);
            playerIcon->show();
        }

    }

}

void GameWindow::RenderArrowButtons() {

    QPixmap bkgnd;
    QMatrix rm;

    for(int i = 0; i < this->game->GetBoardSize() - 1; i++) {

        if(i % 2 == 0) {
            continue;
        }

        // Left
        QPushButton *arrowButton = new QPushButton(this->centralWidget());
        arrowButton->setGeometry(350, ((i + 1) * 72) + 18,72,72);
        arrowButton->setFlat(true);
        bkgnd = QPixmap(":/images/buttons/Arrow");
        rm = QMatrix();
        rm.rotate(0);
        bkgnd = bkgnd.transformed(rm);
        arrowButton->setIcon(bkgnd);
        arrowButton->setIconSize(QSize(72,72));
        arrowButton->setAutoFillBackground(true);
        arrowButton->setStyleSheet("QPushButton{background: transparent;}");
        arrowButton->show();
        QObject::connect(arrowButton, &QPushButton::clicked, [=] {InsertStone(i, 0);});

        // Top
        arrowButton = new QPushButton(this->centralWidget());
        arrowButton->setGeometry(350  + (72 * (i + 1)), 18,72,72);
        arrowButton->setFlat(true);
        bkgnd = QPixmap(":/images/buttons/Arrow");
        rm = QMatrix();
        rm.rotate(90);
        bkgnd = bkgnd.transformed(rm);
        arrowButton->setIcon(bkgnd);
        arrowButton->setIconSize(QSize(72,72));
        arrowButton->setAutoFillBackground(true);
        arrowButton->setStyleSheet("QPushButton{background: transparent;}");
        arrowButton->show();
        QObject::connect(arrowButton, &QPushButton::clicked, [=] {InsertStone(0, i);});

        // Right
        arrowButton = new QPushButton(this->centralWidget());
        arrowButton->setGeometry(422 + (72 * this->game->GetBoardSize()),((i + 1) * 72) + 18,72,72);
        arrowButton->setFlat(true);
        bkgnd = QPixmap(":/images/buttons/Arrow");
        rm = QMatrix();
        rm.rotate(180);
        bkgnd = bkgnd.transformed(rm);
        arrowButton->setIcon(bkgnd);
        arrowButton->setIconSize(QSize(72,72));
        arrowButton->setAutoFillBackground(true);
        arrowButton->setStyleSheet("QPushButton{background: transparent;}");
        arrowButton->show();
        QObject::connect(arrowButton, &QPushButton::clicked, [=] {InsertStone(i, this->game->GetBoardSize() - 1);});

        // Bottom
        arrowButton = new QPushButton(this->centralWidget());
        arrowButton->setGeometry(350 + (72 * (i + 1)), (this->game->GetBoardSize() * 72) + 90,72,72);
        arrowButton->setFlat(true);
        bkgnd = QPixmap(":/images/buttons/Arrow");
        rm = QMatrix();
        rm.rotate(270);
        bkgnd = bkgnd.transformed(rm);
        arrowButton->setIcon(bkgnd);
        arrowButton->setIconSize(QSize(80,80));
        arrowButton->setAutoFillBackground(true);
        arrowButton->setStyleSheet("QPushButton{background: transparent;}");
        arrowButton->show();
        QObject::connect(arrowButton, &QPushButton::clicked, [=] {InsertStone(this->game->GetBoardSize() - 1, i);});



    }

}

void GameWindow::RenderGameBoard() {

    Stone *stone;
    QPushButton *stoneButton;
    vector<Player*> players;

    for(int i = 0; i < this->game->GetBoardSize(); i++) {
        for(int j = 0; j< this->game->GetBoardSize(); j++){
            stone = game->GetStone(j, i);
            QPixmap *pixmap = new QPixmap(72, 72);
            pixmap->fill(Qt::transparent);
            QPainter *painter=new QPainter(pixmap);
            painter->drawPixmap(0,0,72,72,GetStoneImage(stone));

            if(stone->GetTreasure() != 0) {
                QString res = ":/images/items/Item" +
                        QString::number(stone->GetTreasure());
                QPixmap player(res);
                painter->drawPixmap(11,11,50,50,player);
            }

            if(stone->HasPlayer()) {
                for(auto p : stone->GetPlayers()) {
                    QString res = ":/images/players/Player" +
                            QString::number(p->GetPlayerId());
                    QPixmap player(res);
                    painter->drawPixmap(11,11,50,50,player);
                }
            }

            stoneButton = new QPushButton(this->centralWidget());
            stoneButton->setGeometry((i * 72) + 422, (j * 72) + 90,72,72);
            stoneButton->setFlat(true);
            stoneButton->setIcon(*pixmap);
            stoneButton->setIconSize(QSize(72,72));
            stoneButton->setAutoFillBackground(true);

            QObject::connect(stoneButton, &QPushButton::clicked, [=] {MovePlayer(j, i);});

            stoneButton->show();


        }

    }


}


/*********************************************
 * Slots
 */

void GameWindow::SaveGame() {

    if(!QDir("./example").exists()) {
        QDir().mkdir("./example");
    }

    QString fileName;
    fileName = QFileDialog::getSaveFileName(this,
        tr("Save game"), "./example/");

    if(!fileName.isEmpty()) {
        this->game->SaveGame(fileName.toStdString());
    }

}

void GameWindow::RotateStone() {
    this->game->GetFreeStone()->Rotate();
    this->RenderFreeStone();
}

void GameWindow::UndoAction() {

    if(!game->stoneInserted && !game->playerMoved) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("You have not done any actions yet.");
        msgBox.setModal(true);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    this->game->UndoAction(this->game->GetCurrentPlayer());
    this->RenderGameBoard();
    this->RenderFreeStone();
    this->RenderPlayerPanel();
}


void GameWindow::ShowAchievedCards() {
    QDialog *dialog = new QDialog(this);
    int cardsToAchieve = HoldingTreasure::cards / HoldingTreasure::players;
    dialog->setGeometry(10,10,80 + cardsToAchieve * 60, 10 + this->game->GetPlayerCount() * 60);

    Qt::WindowFlags flags = Qt::Window | Qt::WindowSystemMenuHint
                                | Qt::WindowMinimizeButtonHint
                                | Qt::WindowCloseButtonHint;

    dialog->setWindowFlags(flags);

    for(Player *player : game->GetPlayerList()) {

        QRect rectPlayer, rectCard;
        int cnt;

        rectPlayer = QRect(10,10 + (player->GetPlayerId() - 1) * 60 ,50,50);

        QString res = ":/images/players/Player" +
                QString::number(player->GetPlayerId());
        QPixmap pixmap(res);
        QWidget *playerIcon = new QWidget(dialog);
        playerIcon->setGeometry(rectPlayer);
        QPalette palette;
        palette.setBrush(QPalette::Background,QBrush(pixmap));
        playerIcon->setAutoFillBackground(true);
        playerIcon->setPalette(palette);
        playerIcon->show();

        cnt = 0;

        for(TreasureCard *card : *(player->GetHoldingTreasure()->GetAchievedCards())) {

            rectCard = QRect(60 + cnt * 60, 10 + (player->GetPlayerId() - 1) * 60, 50, 50);

            QString res = ":/images/items/Item" +
                    QString::number(card->GetCardNumber());
            QPixmap pixmap(res);
            QWidget *playerIcon = new QWidget(dialog);
            playerIcon->setGeometry(rectCard);
            QPalette palette;
            palette.setBrush(QPalette::Background,QBrush(pixmap));
            playerIcon->setAutoFillBackground(true);
            playerIcon->setPalette(palette);
            playerIcon->show();

            cnt++;

        }

    }

    dialog->exec();

}


void GameWindow::InsertStone(int x, int y) {

    if(game->stoneInserted) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("You have already inserted stone in this round.");
        msgBox.setModal(true);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    try {
        this->game->AddStone(x, y);
    } catch (StoneInsertException *ex) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText(QString::fromStdString(ex->GetMessage()));
        msgBox.setModal(true);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    game->stoneInserted  = true;
    this->RenderFreeStone();
    this->RenderGameBoard();
}



void GameWindow::MovePlayer(int x, int y) {

    if(!game->stoneInserted) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("You have to insert stone first.");
        msgBox.setModal(true);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    if(game->playerMoved) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("You have already moved in this round.");
        msgBox.setModal(true);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    try {
        this->game->MovePlayer(this->game->GetCurrentPlayer(), x, y);
    } catch (AbsentPathException *ex) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText(QString::fromStdString(ex->GetMessage()));
        msgBox.setModal(true);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    game->playerMoved = true;

    Player *currentPlayer = this->game->GetCurrentPlayer();

    if(currentPlayer->GetHoldingTreasure()->CheckForVictory()) {
        this->RenderPlayerPanel();
        this->RenderGameBoard();
        QMessageBox msgBox;
        msgBox.setWindowTitle("Congratulations!");
        msgBox.setText("Player " + QString::number(currentPlayer->GetPlayerId()) +
                       " won the game!");
        msgBox.setModal(true);
        QString res = ":/images/players/Player" +
                QString::number(currentPlayer->GetPlayerId());
        QPixmap pixmap(res);
        msgBox.setIconPixmap(pixmap);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();

        this->CreateWindow();
        return;
    }

    this->RenderPlayerPanel();
    this->RenderGameBoard();

}


void GameWindow::EndTurn() {

    if(!game->stoneInserted) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("You have to insert stone first.");
        msgBox.setModal(true);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    if(!game->playerMoved) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setText("You did not move your character. Do you really want to end your turn?");
        msgBox.setModal(true);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Abort);
        msgBox.setDefaultButton(QMessageBox::Ok);
        if(msgBox.exec() == QMessageBox::Abort) {
            return;
        }
    }

    this->game->NextPlayer();
    game->stoneInserted = false;
    game->playerMoved = false;
    //this->game->SetPlayersOnBoard();

    if(this->game->GetCurrentPlayer()->GetTreasureCard() == NULL) {
        this->game->GetCurrentPlayer()->SetTreasureCard(game->PopCard());
    }

    this->game->previousInsert.xPosition = -1;
    this->game->previousInsert.yPosition = -1;
    this->game->previousInsertTmp.xPosition = -1;
    this->game->previousInsertTmp.yPosition = -1;
    this->game->previousPosition.xPosition = -1;
    this->game->previousPosition.yPosition = -1;
    this->game->takenTreasure = 0;
    this->game->stoneInserted = false;
    this->game->playerMoved = false;
    this->game->itemTaken = false;
    this->game->isUndo = false;

    this->RenderPlayerPanel();
}

void GameWindow::LoadGame() {

    if(this->game == NULL) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Game could not be loaded.");
        msgBox.setModal(true);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    if(this->game->GetCurrentPlayer()->GetTreasureCard() == NULL) {
        this->game->GetCurrentPlayer()->SetTreasureCard(game->PopCard());
    }

    HoldingTreasure::players = this->game->GetPlayerCount();
    HoldingTreasure::cards = this->game->GetPackSize();

    this->game->SetPlayersOnBoard();

    this->SetWindowSize();
    this->RenderRotateButton();
    this->RenderFreeStone();
    this->RenderUndoButton();
    this->RenderAchievedCard();
    this->RenderEndTurnButton();
    this->RenderPlayerPanel();
    this->RenderArrowButtons();
    this->RenderGameBoard();

}
