/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: stone.cpp
 * Description: Source code of functions defined in file stone.h.
 ***************************************************************************************/

#include <stone.h>
#include <iostream>

using namespace std;

Stone::Stone() {
    this->hasPlayer = false;
    this->treasure = 0;
    this->players.clear();
}

Stone::~Stone()     {

}

void Stone::SetStone(StoneType stoneType, StoneRotation rotationType){
    this->actualRotationType = rotationType;
    this->stoneType = stoneType;
    switch(stoneType) {
        case StoneType::_ST_I: {
            switch(rotationType) {
                case StoneRotation::_SR_T: {
                    this->freePaths.TOP = 1;
                    this->freePaths.RIGHT = 0;
                    this->freePaths.BOTTOM = 1;
                    this->freePaths.LEFT = 0;
                } break;
                case StoneRotation::_SR_R: {
                    this->freePaths.TOP = 0;
                    this->freePaths.RIGHT = 1;
                    this->freePaths.BOTTOM = 0;
                    this->freePaths.LEFT = 1;
                } break;
                case StoneRotation::_SR_B: {
                    this->freePaths.TOP = 1;
                    this->freePaths.RIGHT = 0;
                    this->freePaths.BOTTOM = 1;
                    this->freePaths.LEFT = 0;
                } break;
                case StoneRotation::_SR_L: {
                    this->freePaths.TOP = 0;
                    this->freePaths.RIGHT = 1;
                    this->freePaths.BOTTOM = 0;
                    this->freePaths.LEFT = 1;
                } break;
            }
        } break;
        case StoneType::_ST_L: {
            switch(rotationType) {
                case StoneRotation::_SR_T: {
                    this->freePaths.TOP = 1;
                    this->freePaths.RIGHT = 1;
                    this->freePaths.BOTTOM = 0;
                    this->freePaths.LEFT = 0;
                } break;
                case StoneRotation::_SR_R: {
                    this->freePaths.TOP = 0;
                    this->freePaths.RIGHT = 1;
                    this->freePaths.BOTTOM = 1;
                    this->freePaths.LEFT = 0;
                } break;
                case StoneRotation::_SR_B: {
                    this->freePaths.TOP = 0;
                    this->freePaths.RIGHT = 0;
                    this->freePaths.BOTTOM = 1;
                    this->freePaths.LEFT = 1;
                } break;
                case StoneRotation::_SR_L: {
                    this->freePaths.TOP = 1;
                    this->freePaths.RIGHT = 0;
                    this->freePaths.BOTTOM = 0;
                    this->freePaths.LEFT = 1;
                } break;
            }
        } break;
        case StoneType::_ST_T: {
            switch(rotationType) {
                case StoneRotation::_SR_T: {
                    this->freePaths.TOP = 0;
                    this->freePaths.RIGHT = 1;
                    this->freePaths.BOTTOM = 1;
                    this->freePaths.LEFT = 1;
                } break;
                case StoneRotation::_SR_R: {
                    this->freePaths.TOP = 1;
                    this->freePaths.RIGHT = 0;
                    this->freePaths.BOTTOM = 1;
                    this->freePaths.LEFT = 1;
                } break;
                case StoneRotation::_SR_B: {
                    this->freePaths.TOP = 1;
                    this->freePaths.RIGHT = 1;
                    this->freePaths.BOTTOM = 0;
                    this->freePaths.LEFT = 1;
                } break;
                case StoneRotation::_SR_L: {
                    this->freePaths.TOP = 1;
                    this->freePaths.RIGHT = 1;
                    this->freePaths.BOTTOM = 1;
                    this->freePaths.LEFT = 0;
                } break;
            }
        } break;
    }
}

void Stone::AddPlayer(Player *player) {
    this->players.push_back(player);
}

void Stone::SetPlayers(std::vector<Player*> players) {
    this->players = players;
}

void Stone::RemovePlayer(int playerId) {

    if(this->players.empty()) {
        return;
    }

    for(auto iterator = begin(this->players); iterator != end(this->players); iterator++) {
        if((*iterator)->GetPlayerId() == playerId) {
            this->players.erase(iterator);
            return;
        }
    }

}

void Stone::RemovePlayers() {
    this->players.clear();
}

std::vector<Player *> Stone::GetPlayers() {
    return this->players;
}

Player *Stone::GetPlayer(int playerId) {
    if(this->players.empty()) {
        return NULL;
    }

    for(auto i = begin(this->players); i != end(this->players); i++) {
        if((*i)->GetPlayerId() == playerId) {
            return *i;
        }
    }

    return NULL;
}

bool Stone::HasPlayer() {
    return !this->players.empty();
}

StoneType Stone::GetStoneType() {
    return this->stoneType;
}

void Stone::SetStoneType(StoneType type) {
    this->stoneType = type;
}

StoneRotation Stone::GetRotationType() {
    return this->actualRotationType;
}

void Stone::SetRotationType(StoneRotation rotation) {
    this->actualRotationType = rotation;
}

Paths Stone::GetPaths() {
    return this->freePaths;
}

Treasure Stone::GetTreasure() {
    return this->treasure;
}

void Stone::SetTreasure(Treasure treasure) {
    this->treasure = treasure;
}

void Stone::Rotate() {
    char tmpRotation;
    tmpRotation = this->freePaths.TOP;
    this->freePaths.TOP = this->freePaths.LEFT;
    this->freePaths.LEFT = this->freePaths.BOTTOM;
    this->freePaths.BOTTOM = this->freePaths.RIGHT;
    this->freePaths.RIGHT = tmpRotation;

    switch(this->actualRotationType) {
        case StoneRotation::_SR_L:
            this->actualRotationType = StoneRotation::_SR_T;
            break;
        case StoneRotation::_SR_T:
            this->actualRotationType = StoneRotation::_SR_R;
            break;
        case StoneRotation::_SR_R:
            this->actualRotationType = StoneRotation::_SR_B;
            break;
        case StoneRotation::_SR_B:
            this->actualRotationType = StoneRotation::_SR_L;
            break;
    }
}
