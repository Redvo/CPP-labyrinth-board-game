/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: game.h
 * Description: This header file contains class Game which holds methods and 
 *              properties describing object representing running game.
 ***************************************************************************************/

#ifndef GAME_H
#define GAME_H

#include <types.h>
#include <cardpack.h>
#include <gameboard.h>
#include <playerlist.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

//! Class GameBoard
/*!
This header file contains class Game which holds methods and 
properties describing object representing running game.
*/
class Game : public CardPack, public GameBoard, public PlayerList
{
    public:
        //! Constructor of game object.
        /*!
            \param  boardSize   size of game board.
            \param  cardCount   number of cards.
            \param  playerCount number of players

        */
        Game(BoardSize boardSize, CardCount cardCount, PlayerCount playerCount);
        //! Destructor of game object.
        ~Game();
        //! Getter for game board size.
        /*!
            \return size of game board.
        */
        BoardSize GetBoardSize();
        //! Getter for size of card pack.
        /*!
            \return number of cards.
        */
        CardCount GetPackSize();
        //! Getter for number of players.
        /*!
            \return number of players.
        */
        PlayerCount GetPlayerCount();
        //! Assigns player objects to stones.
        void SetPlayersOnBoard();
        //! Split string by delimiter to vector of strings.
        /*!
            \param  str         string to split
            \param  delimiter   delimiter
            \return vector of string.
        */
        static std::vector<std::string> StringSplit(std::string str, char delimiter);
        //! Saves current game to file.
        /*!
            \param  filename    filename of file to save the game.
        */
        void SaveGame(std::string filename);
        //! Load game from file.
        /*!
            \param  filename    filename of file to load the game.
            \return game object of loaded game.
        */
        static Game *LoadGame(std::string filename);
        //! Crate new game object.
        /*!
            \param  boardSize   size of game board.
            \param  cardCount   number of cards.
            \param  playerCount number of players
        */
        static Game *NewGame(BoardSize boardSize, CardCount cardCount, PlayerCount playerCount);

    private:
        BoardSize boardSize; /*!< Size of game board. */
        CardCount cardCount; /*!< Number of cards. */
        PlayerCount playerCount; /*!< Number of players. */
};

#endif // GAME_H

/* End of file game.h */