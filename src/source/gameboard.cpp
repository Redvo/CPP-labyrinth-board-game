/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: gameboard.cpp
 * Description: Source code of functions defined in file gameboard.h.
 ***************************************************************************************/

#include <gameboard.h>

using namespace std;

GameBoard::GameBoard(BoardSize boardSize) {
    this->boardSize = boardSize;
    this->previousInsert.xPosition = -1;
    this->previousInsert.yPosition = -1;
    this->previousInsertTmp.xPosition = -1;
    this->previousInsertTmp.yPosition = -1;
    this->previousPosition.xPosition = -1;
    this->previousPosition.yPosition = -1;
    this->takenTreasure = 0;
    this->stoneInserted = false;
    this->playerMoved = false;
    this->itemTaken = false;
    this->isUndo = false;
}

GameBoard::~GameBoard() {

}

void GameBoard::CreateStones() {
    this->stones = new Stone*[this->boardSize]();
    for(int i=0; i < this->boardSize; i++) {
        this->stones[i] = new Stone[this->boardSize]();
    }
}

void GameBoard::DeleteStones() {
    for(int i=0; i < this->boardSize; i++) {
        free(this->stones[i]);
    }
    free(this->stones);
}

void GameBoard::SplitStones() {
    int stoneCount = (this->boardSize * this->boardSize) + 1;
    int splitPart = stoneCount / 3;
    int restPart = stoneCount % 3;
    this->stonesI = splitPart;
    if(restPart > 0) {
        this->stonesI++;
        restPart--;
    }
    stoneCount -= splitPart;
    this->stonesL = splitPart;
    if(restPart > 0) {
        this->stonesL++;
        restPart--;
    }
    stoneCount -= splitPart;
    this->stonesT = stoneCount;
}

void GameBoard::InitializeStones() {

    int i, j, randomType, randomRotation;
    int stonesT = this->stonesT;
    int stonesI = this->stonesI;
    int stonesL = this->stonesL;
    srand (time(NULL));

    this->stones[0][0].SetStone(StoneType::_ST_L, StoneRotation::_SR_R);
    this->stones[0][this->boardSize - 1].SetStone(StoneType::_ST_L, StoneRotation::_SR_B);
    this->stones[this->boardSize - 1][0].SetStone(StoneType::_ST_L, StoneRotation::_SR_T);
    this->stones[this->boardSize - 1][this->boardSize - 1].SetStone(StoneType::_ST_L, StoneRotation::_SR_L);
    stonesL -= 4;
    for(i = 2; i < (this->boardSize - 2); i++) {
        if(i % 2 == 1) {
            continue;
        }

        this->stones[0][i].SetStone(StoneType::_ST_T, StoneRotation::_SR_T);
        this->stones[this->boardSize - 1][i].SetStone(StoneType::_ST_T, StoneRotation::_SR_B);
        this->stones[i][0].SetStone(StoneType::_ST_T, StoneRotation::_SR_L);
        this->stones[i][this->boardSize - 1].SetStone(StoneType::_ST_T, StoneRotation::_SR_R);
        stonesT -= 4;
    }

    for(i = 2; i < (this->boardSize - 2); i++) {
        for(j = 2; j < (this->boardSize - 2); j++) {
            if(i % 2 == 0 && j % 2 == 0) {
                StoneRotation rotation = static_cast<StoneRotation>(rand() % 4);
                this->stones[i][j].SetStone(StoneType::_ST_T, rotation);
            }
        }
    }

    for(i = 0; i < this->boardSize; i++) {
        for(j = 0; j < this->boardSize; j++) {
            if((((i == 0) || (i == (this->boardSize - 1))) && j % 2 == 0) ||
                (((j == 0) || (j == (this->boardSize - 1))) && i % 2 == 0) ||
                    (i % 2 == 0 && j % 2 == 0)) {
                continue;
            }

            randomType = (rand() % 3);
            randomRotation = (rand() % 4);

            switch(randomType) {
                case StoneType::_ST_L: {
                    if(stonesL > 0) {
                        this->stones[i][j].SetStone(StoneType::_ST_L,
                                                    static_cast<StoneRotation>(randomRotation));
                        stonesL--;
                    } else if(stonesT > stonesI) {
                        this->stones[i][j].SetStone(StoneType::_ST_T,
                                                    static_cast<StoneRotation>(randomRotation));
                        stonesT--;
                    } else {
                        this->stones[i][j].SetStone(StoneType::_ST_I,
                                                    static_cast<StoneRotation>(randomRotation));
                        stonesI--;
                    }
                } break;
                case StoneType::_ST_T: {
                    if(stonesT > 0) {
                        this->stones[i][j].SetStone(StoneType::_ST_T,
                                                    static_cast<StoneRotation>(randomRotation));
                        stonesT--;
                    } else if(stonesI > stonesL) {
                        this->stones[i][j].SetStone(StoneType::_ST_I,
                                                    static_cast<StoneRotation>(randomRotation));
                        stonesI--;
                    } else {
                        this->stones[i][j].SetStone(StoneType::_ST_L,
                                                    static_cast<StoneRotation>(randomRotation));
                        stonesL--;
                    }
                } break;
                case StoneType::_ST_I: {
                    if(stonesI > 0) {
                        this->stones[i][j].SetStone(StoneType::_ST_I,
                                                    static_cast<StoneRotation>(randomRotation));
                        stonesI--;
                    } else if(stonesL > stonesT) {
                        this->stones[i][j].SetStone(StoneType::_ST_L,
                                                    static_cast<StoneRotation>(randomRotation));
                        stonesL--;
                    } else {
                        this->stones[i][j].SetStone(StoneType::_ST_T,
                                                    static_cast<StoneRotation>(randomRotation));
                        stonesT--;
                    }
                }
            }
        }
    }

    if(stonesL > 0) {
        this->freeStone.SetStone(StoneType::_ST_L, StoneRotation::_SR_B);
    } else if(stonesI > 0) {
        this->freeStone.SetStone(StoneType::_ST_I, StoneRotation::_SR_B);
    } else {
        this->freeStone.SetStone(StoneType::_ST_L, StoneRotation::_SR_B);
    }

}

void GameBoard::RandomSetItems(int cardCount) {

    srand (time(NULL));
    int x, y, randomindex;
    vector<int> randomx, randomy, treasure;

    for(int i = 1; i <= cardCount; i++) {
        treasure.push_back(i);
    }


    random_shuffle (begin(treasure),end(treasure));

    for(int i = 0; i < this->boardSize; i++) {
        for(int j = 0; j < this->boardSize; j++) {
            randomx.push_back(i);
            randomy.push_back(j);
        }
    }

    for(int i = 1; i <= cardCount; i++) {
        randomindex = (rand() % randomx.size());
        x = randomx.at(randomindex);
        y = randomy.at(randomindex);
        randomx.erase(randomx.begin() + randomindex);
        randomy.erase(randomy.begin() + randomindex);

        if(this->stones[x][y].GetTreasure() == 0) {
            this->stones[x][y].SetTreasure(treasure.back());
            treasure.pop_back();
        } else {
            i--;
            continue;
        }
    }

}

void GameBoard::AddStone(int row, int column) {

    Stone freeStone;
    if(!this->isUndo && row == this->previousInsert.xPosition && column == this->previousInsert.yPosition) {
        throw new StoneInsertException("Unable to revert back previous insertion.", ErrorCode::_ERR_UNKNOWN);
    }

    if(!this->isUndo) {
        this->previousInsertTmp.xPosition = this->previousInsert.xPosition;
        this->previousInsertTmp.yPosition = this->previousInsert.yPosition;
    }

    // From top
    if(row == 0 && column < this->boardSize && (column % 2 == 1)) {

        freeStone = this->MoveStones(row, column, Direction::_DIR_DOWN);
        this->previousInsert.xPosition = this->boardSize - 1;
        this->previousInsert.yPosition = column;
        if(freeStone.HasPlayer()) {
            this->freeStone.SetPlayers(freeStone.GetPlayers());
            freeStone.RemovePlayers();
            for(Player *player : this->freeStone.GetPlayers()) {
                player->SetPosition(0, player->GetPosition().yPosition);
            }
        }
        if(freeStone.GetTreasure() != 0) {
            this->freeStone.SetTreasure(freeStone.GetTreasure());
            freeStone.SetTreasure(0);
        }
        this->stones[row][column] = this->freeStone;

    // From bottom
    } else if (row == (this->boardSize - 1) && column < this->boardSize && (column % 2 == 1)) {

        freeStone = this->MoveStones(row, column, Direction::_DIR_UP);
        this->previousInsert.xPosition = 0;
        this->previousInsert.yPosition = column;
        if(freeStone.HasPlayer()) {
            this->freeStone.SetPlayers(freeStone.GetPlayers());
            freeStone.RemovePlayers();
            for(Player *player : this->freeStone.GetPlayers()) {
                player->SetPosition(this->boardSize - 1, player->GetPosition().yPosition);
            }
        }
        if(freeStone.GetTreasure() != 0) {
            this->freeStone.SetTreasure(freeStone.GetTreasure());
            freeStone.SetTreasure(0);
        }
        this->stones[row][column] = this->freeStone;

    // From left
    } else if (column == 0 && row < this->boardSize && (row % 2 == 1)) {

        freeStone = this->MoveStones(row, column, Direction::_DIR_RIGHT);
        this->previousInsert.xPosition = row;
        this->previousInsert.yPosition = this->boardSize - 1;
        if(freeStone.HasPlayer()) {
            this->freeStone.SetPlayers(freeStone.GetPlayers());
            freeStone.RemovePlayers();
            for(Player *player : this->freeStone.GetPlayers()) {
                player->SetPosition(player->GetPosition().xPosition, 0);
            }
        }
        if(freeStone.GetTreasure() != 0) {
            this->freeStone.SetTreasure(freeStone.GetTreasure());
            freeStone.SetTreasure(0);
        }
        this->stones[row][column] = this->freeStone;

    // From right
    } else if (column == (this->boardSize - 1) && row < this->boardSize && (row % 2 == 1)) {

        freeStone = this->MoveStones(row, column, Direction::_DIR_LEFT);
        this->previousInsert.xPosition = row;
        this->previousInsert.yPosition = 0;
        if(freeStone.HasPlayer()) {
            this->freeStone.SetPlayers(freeStone.GetPlayers());
            freeStone.RemovePlayers();
            for(Player *player : this->freeStone.GetPlayers()) {
                player->SetPosition(player->GetPosition().xPosition, this->boardSize - 1);
            }
        }
        if(freeStone.GetTreasure() != 0) {
            this->freeStone.SetTreasure(freeStone.GetTreasure());
            freeStone.SetTreasure(0);
        }
        this->stones[row][column] = this->freeStone;

    } else {

        throw new StoneInsertException("Unable to insert stone on given position.", ErrorCode::_ERR_UNKNOWN);

    }

    this->freeStone = freeStone;

}

Stone GameBoard::MoveStones(int row, int column, Direction vector) {

    Stone outStone;

    switch(vector) {

        case Direction::_DIR_DOWN: {

            outStone = this->stones[this->boardSize-1][column];
            for(int i = this->boardSize - 1; i > 0; i--) {
                this->stones[i][column] = this->stones[i-1][column];
                for(Player *player : this->stones[i][column].GetPlayers()) {
                    player->SetPosition(i, column);
                }
            }

        }; break;

        case Direction::_DIR_UP: {

            outStone = this->stones[0][column];
            for(int i = 0; i < this->boardSize - 1; i++) {
                this->stones[i][column] = this->stones[i+1][column];
                for(Player *player : this->stones[i][column].GetPlayers()) {
                    player->SetPosition(i, column);
                }
            }

        } break;

        case Direction::_DIR_RIGHT: {

            outStone = this->stones[row][this->boardSize - 1];
            for(int i = this->boardSize - 1; i > 0; i--) {
                this->stones[row][i] = this->stones[row][i - 1];
                for(Player *player : this->stones[row][i].GetPlayers()) {
                    player->SetPosition(row, i);
                }
            }

        } break;

        case Direction::_DIR_LEFT: {

            outStone = this->stones[row][0];
            for(int i = 0; i < this->boardSize - 1; i++) {
                this->stones[row][i] = this->stones[row][i+1];
                for(Player *player : this->stones[row][i].GetPlayers()) {
                    player->SetPosition(row, i);
                }
            }

        } break;

    }

    return outStone;

}

Stone *GameBoard::GetStone(int row, int column) {
    return &this->stones[row][column];
}

Stone *GameBoard::GetFreeStone() {
    return &this->freeStone;
}

void GameBoard::SetFreeStone(Stone stone) {
    this->freeStone = stone;
}

bool GameBoard::FindPath(int startX, int startY, int endX, int endY) {

    Stone *stone = this->GetStone(startX, startY);
    Stone *nextStone;
    this->visited.push_back(stone);

    if((stone->GetPaths().TOP == 1) && (startX > 0)) {
        nextStone = this->GetStone(startX - 1, startY);
        if(nextStone->GetPaths().BOTTOM == 1) {
            if (find(begin(this->visited), end(this->visited), nextStone) == end(this->visited)) {
                if((startX-1 == endX && startY == endY) || (this->FindPath(startX-1,startY,endX,endY))) {
                    return true;
                }
            }
        }
    }


    if((stone->GetPaths().LEFT == 1) && (startY > 0)) {
        nextStone = this->GetStone(startX, startY - 1);
        if(nextStone->GetPaths().RIGHT == 1) {
            if (find(begin(this->visited), end(this->visited), nextStone) == end(this->visited)) {
                if((startX == endX && startY-1 == endY) || (this->FindPath(startX,startY-1,endX,endY))) {
                    return true;
                }
            }
        }
    }

    if((stone->GetPaths().BOTTOM == 1) && (startX < (this->boardSize - 1))) {
        nextStone = this->GetStone(startX + 1, startY);
        if(nextStone->GetPaths().TOP == 1) {
            if (find(begin(this->visited), end(this->visited), nextStone) == end(this->visited)) {
                if((startX + 1 == endX && startY == endY) || (this->FindPath(startX + 1,startY,endX,endY))) {
                    return true;
                }
            }
        }
    }

    if((stone->GetPaths().RIGHT == 1) && (startY < (this->boardSize - 1))) {
        nextStone = this->GetStone(startX, startY + 1);
        if(nextStone->GetPaths().LEFT == 1) {
            if (find(begin(this->visited), end(this->visited), nextStone) == end(this->visited)) {
                if((startX == endX && startY + 1 == endY) || (FindPath(startX,startY + 1,endX,endY))) {
                    return true;
                }
            }
        }
    }

    return false;
}

void GameBoard::MovePlayer(Player *player, int row, int column) {

    if(player->GetPosition().xPosition == row && player->GetPosition().yPosition == column) {
        throw new AbsentPathException("Unable to move to the same field.", ErrorCode::_ERR_UNKNOWN);
    }

    int sourceX,sourceY;
    Stone *sstone, *dstone;
    this->visited.clear();
    sourceX = player->GetPosition().xPosition;
    sourceY = player->GetPosition().yPosition;
    if(!this->FindPath(sourceX, sourceY, row, column)) {
        throw new AbsentPathException("Unable to move to that field. Path does not exist.", ErrorCode::_ERR_UNKNOWN);
    }
    this->previousPosition.xPosition = sourceX;
    this->previousPosition.yPosition = sourceY;
    sstone = this->GetStone(sourceX,sourceY);
    dstone = this->GetStone(row, column);
    sstone->RemovePlayer(player->GetPlayerId());
    dstone->AddPlayer(player);
    player->SetPosition(row, column);
    if(dstone->GetTreasure() == player->GetTreasureCard()->GetCardNumber()) {
        this->takenTreasure = player->GetTreasureCard()->GetCardNumber();
        player->GetHoldingTreasure()->AchieveCard(player->GetTreasureCard());
        player->SetTreasureCard(NULL);
        dstone->SetTreasure(static_cast<Treasure>(0));
        this->itemTaken = true;
    }

}

void GameBoard::UndoAction(Player *player) {

    Stone *sstone = NULL, *dstone = NULL;
    this->isUndo = true;

    if(this->playerMoved) {
        sstone = this->GetStone(player->GetPosition().xPosition, player->GetPosition().yPosition);
        dstone = this->GetStone(this->previousPosition.xPosition, this->previousPosition.yPosition);
        sstone->RemovePlayer(player->GetPlayerId());
        dstone->AddPlayer(player);
        player->SetPosition(this->previousPosition.xPosition, this->previousPosition.yPosition);
        this->playerMoved = false;
    }

    if(this->itemTaken) {
    	if(player->GetHoldingTreasure()->GetAchievedCards() != NULL) {
        	player->GetHoldingTreasure()->GetAchievedCards()->pop_back();
    	}
        player->SetTreasureCard(new TreasureCard(this->takenTreasure));
        sstone->SetTreasure(static_cast<Treasure>(this->takenTreasure));
        this->takenTreasure = 0;
        this->itemTaken = false;
    }
    
    if(this->stoneInserted) {
        this->AddStone(this->previousInsert.xPosition, this->previousInsert.yPosition);
        this->previousInsert.xPosition = this->previousInsertTmp.xPosition;
        this->previousInsert.yPosition = this->previousInsertTmp.yPosition;
        this->stoneInserted = false;
    }

    this->previousInsert.xPosition = -1;
    this->previousInsert.yPosition = -1;
    this->previousInsertTmp.xPosition = -1;
    this->previousInsertTmp.yPosition = -1;
    this->previousPosition.xPosition = -1;
    this->previousPosition.yPosition = -1;

    this->isUndo = false;
    
}

/* End of file gameboard.cpp */
