/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: holdingtreasure.cpp
 * Description: Source code of functions defined in file holdingtreasure.h.
 ***************************************************************************************/

#include <holdingtreasure.h>

using namespace std;

int HoldingTreasure::cards = 0;
int HoldingTreasure::players = 0;

HoldingTreasure::HoldingTreasure()
{

}

HoldingTreasure::~HoldingTreasure()
{

}

/*! shows all achieved cards,parameter is vector of all achieved cards */
vector<TreasureCard*> *HoldingTreasure::GetAchievedCards() {
   return &this->achievedCards;
}

/*! game finish - C/P = number of cards - now only print----- FINISH --- */
bool HoldingTreasure::CheckForVictory () {
    if (static_cast<unsigned int>(HoldingTreasure :: cards / HoldingTreasure :: players)
        == this->achievedCards.size()) {
            return true;
    }
    return false;
}

/*! function add new card to holding treasure container and return in back to player */
void HoldingTreasure::AchieveCard(TreasureCard *item) {
    this->achievedCards.push_back(item);
    return;
}
