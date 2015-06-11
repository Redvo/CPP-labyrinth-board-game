/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: playerlist.cpp
 * Description: Source code of functions defined in file playerlist.h.
 ***************************************************************************************/

#include <playerlist.h>

using namespace std;

PlayerList::PlayerList(PlayerCount playerCount, BoardSize boardSize) {
    this->playerCount = playerCount;
    this->boardSize = boardSize;
    this->player = 0;
    this->currentPlayer = NULL;

}

PlayerList::PlayerList() {

}

PlayerList::~PlayerList()
{

}

void PlayerList::NextPlayer() {

    if(static_cast<unsigned int>(this->player + 1) == this->playerList.size()) {
        this->player = 0;
    } else {
        this->player++;
    }

    this->currentPlayer = this->playerList[this->player];

}

Player *PlayerList::GetCurrentPlayer() {
    return this->currentPlayer;
}

void PlayerList::SetCurrentPlayer(Player *player) {
    this->currentPlayer = player;
    this->player = player->GetPlayerId() - 1;
}

void PlayerList::InitializePlayerList() {

    PlayerPosition position;
    Player *player;

    if(this->playerCount == 2) {

        player = new Player(position = {0, 0}, new HoldingTreasure(), 1);
            this->playerList.push_back(player);
        player = new Player(position = {this->boardSize - 1, this->boardSize - 1}, new HoldingTreasure(), 2);
            this->playerList.push_back(player);

    } else {

        for(unsigned char i = 0; i < this->playerCount; ++i) {

            switch(i) {
                case 0: {
                    player = new Player(position = {0, 0}, new HoldingTreasure(), 1);
                        this->playerList.push_back(player);
                } break;
                case 1: {
                    player = new Player(position = {0, this->boardSize -1}, new HoldingTreasure(), 2);
                    this->playerList.push_back(player);
                } break;
                case 2: {
                    player = new Player(position = {this->boardSize - 1, this->boardSize - 1}, new HoldingTreasure(), 3);
                        this->playerList.push_back(player);
                } break;
                case 3: {
                    player = new Player(position = {this->boardSize -1, 0}, new HoldingTreasure(), 4);
                        this->playerList.push_back(player);
                } break;
                default: break;
            }

        }

    }

    this->currentPlayer = this->playerList.at(0);

}

vector<Player*> PlayerList::GetPlayerList() {
    return this->playerList;
}

void PlayerList::AddPlayer(Player *player) {
    this->playerList.push_back(player);
}

Player *PlayerList::FindPlayer(int playerId) {
    for(Player *player : this->playerList) {
        if(player->GetPlayerId() == playerId) {
            return player;
        }
    }
    return NULL;
}