/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: holdingtreasure.h
 * Description: This header file contains class HoldingTreasure which holds methods and 
 *              properties describing object of players achieved cards.
 ***************************************************************************************/

#ifndef HOLDINGTREASURE_H
#define HOLDINGTREASURE_H

#include <treasurecard.h>
#include <vector>

//! Class Player
/*!
This header file contains class HoldingTreasure which holds methods and 
properties describing object of players achieved cards.
*/
class HoldingTreasure
{
    public:

        static int players; /*!< Static variable storing number of players in game (for victory check). */ 
        static int cards; /*!< Static variable storing number of cards in game (for victory check). */ 

        //! Constructor of holding treasure object.
        HoldingTreasure();
        //! Destructor of holding treasure object.
        ~HoldingTreasure();
        //! Getter for players achieved cards.
        /*!
            \return vector of all achieved cards of player.
        */
        std::vector<TreasureCard *> *GetAchievedCards();
        //! FUnction checks if player wins the game. Condition is to achieve number of cards = total cards / total players.
        /*!
            \return true if player wins the game, false otherwise.
        */
        bool CheckForVictory ();
        //! Setter for players achieved cards.
        /*!
            \param  item    treasure card to be add between achieved cards.
        */
        void AchieveCard(TreasureCard *item);

    private:
        std::vector<TreasureCard*> achievedCards; /*!< Vector representing players achieved cards. */
};

#endif // HOLDINGTREASURE_H

/* End of file holdingtreasure.h */