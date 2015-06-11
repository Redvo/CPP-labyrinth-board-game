/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: player.cpp
 * Description: Source code of functions defined in file player.h.
 ***************************************************************************************/

#include <player.h>

using namespace std;

Player::Player(PlayerPosition position, HoldingTreasure *holdingTreasure, int playerId) {
    this->position.xPosition = position.xPosition;
    this->position.yPosition = position.yPosition;
    this->holdingTreasure = holdingTreasure;
    this->playerId = playerId;
    this->treasureCard = NULL;
}

Player::~Player(){

}

PlayerPosition Player::GetPosition() {
    return this->position;
}

void Player::SetPosition(int x, int y) {
    this->position.xPosition = x;
    this->position.yPosition = y;
}

int Player::GetPlayerId() {
    return this->playerId;
}

void Player::SetTreasureCard(TreasureCard *treasureCard) {
    this->treasureCard = treasureCard;
}

HoldingTreasure *Player::GetHoldingTreasure() {
    return this->holdingTreasure;
}

TreasureCard *Player::GetTreasureCard() {
    return this->treasureCard;
}
