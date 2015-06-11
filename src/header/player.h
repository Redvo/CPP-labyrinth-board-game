/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: player.h
 * Description: This header file contains class Player which holds methods and 
 *              properties describing object of single player in a game.
 ***************************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include <types.h>
#include <treasurecard.h>
#include <holdingtreasure.h>
#include <vector>
#include <string>

//! Class Player
/*!
This header file contains class Player which holds methods and 
properties describing object of single player in a game.
*/
class Player
{
    public:
        //! Constructor of player object.
        /*!
            \param  position            initial position of player on game board.
            \param  holdingTreasure     initial empty holdin treasure of this player.
            \param  playerId            unique numeric identificator of this player.
        */
        Player(PlayerPosition position, HoldingTreasure *holdingTreasure, int playerId);
        //! Descriptionstructor of player object.
        ~Player();
        //! Getter for position of player.
        /*!
            \return position of this player.
        */
        PlayerPosition GetPosition();
        //! Setter for position of player.
        /*!
            \param  x   X coordinate on game board.
            \param  y   Y coordinate on game board.
        */
        void SetPosition(int x, int y);
        //! Getter for numeric identificator of player.
        /*!
            \return unique numeric identificator of player.
        */
        int GetPlayerId();
        //! Setter for treasure card. Adds treasure card to players hand.
        /*!
            \param  treasureCard    pointer to object representing treasure card.
        */
        void SetTreasureCard(TreasureCard *treasureCard);
        //! Getter for treasure card. Returns treasure card in players hand.
        /*!
            \return pointer to object representing treasure card.
        */
        TreasureCard *GetTreasureCard();
        //! Getter for players holding treasure.
        /*!
            \return pointer to object representing all achieved cards.
        */
        HoldingTreasure *GetHoldingTreasure();

    private:
        int playerId; /*!< Numeric identificator of this player. */ 
        PlayerPosition position; /*!< Position of this player. */ 
        HoldingTreasure *holdingTreasure; /*!< Achieved cards of this player. */ 
        TreasureCard *treasureCard; /*!< Card in this players hand. */ 
};

#endif // PLAYER_H

/* End of file player.h */