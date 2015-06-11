/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: cardpack.h
 * Description: This header file contains class CardPack which holds methods and 
 *              properties describing object representing pack of all cards.
 ***************************************************************************************/

#ifndef CARDPACK_H
#define CARDPACK_H

#include <treasurecard.h>
#include <ctime>
#include <vector>
#include <algorithm>

//! Class GameBoard
/*!
This header file contains class CardPack which holds methods and 
properties describing object representing pack of all cards.
*/
class CardPack
{
    public:
        //! Constructor of game object.
        /*!
            \param  initSize    size of card pack.
        */
        CardPack(int initSize);
        //! Destructor of game object.
        ~CardPack();
        //! Function creates and populates card pack by unique values.
        void CreateCardPack();
        //! Function returns top card from card pack.
        /*!
            \return treasure card object representing top card from card pack.
        */
        TreasureCard *PopCard();
        //! Getter for size of card pack.
        /*!
            \return size of card pack.
        */
        int  GetPackSize();
        //! Function randomly shuffles the card pack.
        void ShufflePack();
        //! Getter for vector of treasure cards representing card pack.
        /*!
            \return vector of treasure cards.
        */
        std::vector<TreasureCard*> GetCardPack();
        //! Add a card to card pack.
        /*!
            \param  treasureCard    treasure card object.
        */
        void AddToCardPack(TreasureCard *treasureCard);

    private:
        std::vector<TreasureCard*> cardPack; /*!< Vector representing card pack. */
        CardCount initSize; /*!< Number of cards. */
};

#endif // CARDPACK_H

/* End of file cardpack.h */