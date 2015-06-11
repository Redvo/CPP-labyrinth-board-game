/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: playerlist.h
 * Description: This header file contains class PlayerList which holds methods and 
 *              properties describing object of list of all players in a game.
 ***************************************************************************************/

#ifndef PLAYERLIST_H
#define PLAYERLIST_H

#include <types.h>
#include <player.h>
#include <vector>
#include <iostream>

//! Class PlayerList
/*!
This header file contains class PlayerList which holds methods and 
properties describing object of list of all players in a game.
*/
class PlayerList
{

    public:
        //! Constructor of player list object.
        /*!
            \param  playerCount number of players in game.
            \param  boardSize   size of game board.
        */
        PlayerList(PlayerCount playerCount, BoardSize boardSize);
        //! Constructor of player list object.
        PlayerList();
        //! Destructor of player list object.
        ~PlayerList();
        //! This function initializes list of players. 
        /*!
            It creates all player objects and sets their initial positions, holding treasures and numeric identificators.
        */
        void InitializePlayerList();
        //! This function passes move to next player. 
        /*!
            It changes current playr identificator and pointer to current player.
        */
        void NextPlayer();
        //! Search for object of player identified by unique ID.
        /*!
            \param  playerId    unique player identificator.
            \return Pointer to player object.
        */
        Player *FindPlayer(int playerId);
        //! Getter for object of player currently on move.
        /*!
            \return Pointer to player object.
        */
        Player *GetCurrentPlayer();
        //! Setter for object of player currently on move.
        /*!
            \param  player  Pointer to player object.
        */
        void SetCurrentPlayer(Player *player);
        //! Getter for list of players.
        /*!
            \return Vector representing list of players.
        */
        std::vector<Player*> GetPlayerList();
        //! Add player to player list.
        /*!
            \param  player to be add to list.
        */
        void AddPlayer(Player *player);

    private:
        int player; /*!< Numeric identificator of player currently on move. */ 
        Player *currentPlayer; /*!< Pointer to player object currently on move. */
        PlayerCount playerCount; /*!< Number of players in list (and in game). */
        BoardSize boardSize; /*!< Size of game board (needed to deterine starting positions of players). */
        std::vector<Player*> playerList; /*!< Vector representing list of players. */
};

#endif // PLAYERLIST_H

/* End of file playerlist.h */