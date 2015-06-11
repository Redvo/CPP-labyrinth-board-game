/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: cardpack.cpp
 * Description: Source code of functions defined in file cardpack.h.
 ***************************************************************************************/

#include <cardpack.h>

using namespace std;

CardPack::CardPack(int initSize) {
      this->initSize = initSize;
}

CardPack::~CardPack() {

}

//function create_card_pack creates array of game cards. Each number represents a treasure object from our game.
void CardPack::CreateCardPack() {
    TreasureCard *treasureCard = NULL;
    for(int i=1; i <= this->initSize; i++){
        treasureCard = new TreasureCard(i);
        this->cardPack.push_back(treasureCard);
    }
}

// return top card of our card package
TreasureCard *CardPack::PopCard(){
    TreasureCard *card = this->cardPack.back();
    this->cardPack.pop_back();
    return card;
}

// return size of card package
int CardPack :: GetPackSize() {
    return this->initSize;
}

// shuffle cards in the packet, generating two random numbers, their values are exchanged
void CardPack::ShufflePack() {
    srand (time(NULL));
    random_shuffle (begin(this->cardPack),end(this->cardPack));
}

std::vector<TreasureCard*> CardPack::GetCardPack() {
    return this->cardPack;
}

void CardPack::AddToCardPack(TreasureCard *treasureCard) {
    this->cardPack.push_back(treasureCard);
}