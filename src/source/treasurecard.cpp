/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: treasurecard.cpp
 * Description: Source code of functions defined in file treasurecard.h.
 ***************************************************************************************/

#include <treasurecard.h>

using namespace std;

TreasureCard::TreasureCard(Treasure cardNumber){
    this->cardNumber = cardNumber;
}

TreasureCard::~TreasureCard() {

}

Treasure TreasureCard::GetCardNumber() {
    return this->cardNumber;
}
