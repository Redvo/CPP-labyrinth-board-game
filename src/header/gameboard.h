/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: gameboard.h
 * Description: This header file contains class GameBoard which holds methods and 
 *              properties describing object representing game board.
 ***************************************************************************************/

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <types.h>
#include <exception.h>
#include <playerlist.h>
#include <stone.h>
#include <ctime>
#include <iostream>
#include <algorithm>

//! Class GameBoard
/*!
This header file contains class GameBoard which holds methods and 
properties describing object representing game board.
*/
class GameBoard
{
    public:
        //! Constructor of game board object.
        /*!
            \param  playerCount number of players in game.
            \param  boardSize   size of game board.
        */
        GameBoard(BoardSize boardSize);
        //! Destructor of game board object.
        ~GameBoard();
        //! This function create two dimensional array of stone objects.
        void CreateStones();
        //! This function count number of each stone type in 1:1:1 ratio.
        void SplitStones();
        //! This function assigns type and rotation to stones.
        void InitializeStones();
        //! This function assignes items to random stones.
        /*!
            \param  cardCount   Number of cards (and items).
        */
        void RandomSetItems(int cardCount);
        //! Insert stone to game board.
        /*!
            \param  i   X position of stone insertion
            \param  j   Y position of stone insertion
        */
        void AddStone(int i, int j);
        //! This is recursive algorithm that search for path between two stones.
        /*!
            \param  startX  X postion of start
            \param  startY  Y position of stone insertion
            \param  endX    X position of stone insertion
            \param  endY    Y position of stone insertion
        */
        bool FindPath(int startX, int startY, int endX, int endY);
        //! Getter for stone on given position
        /*!
            \param  row      X position of stone
            \param  column   Y position of stone
            \return pointer to stone on given position
        */
        Stone *GetStone(int row, int column);
        //! Getter for free stone out of board
        /*!
            \return Pointer to free stone
        */
        Stone *GetFreeStone();
        //! Setter for free stone out of board
        /*!
            \param  stone   Free stone
        */
        void SetFreeStone(Stone stone);
        //! Move player to defined position
        /*!
            \param player  player that should be moved
            \param row     x position where to move player
            \param column  y position where to move player
        */
        void MovePlayer(Player *player, int row, int column);
        //! This function deletes all stone objects.
        void DeleteStones();
        //! This function returns current player move to begining.
        /*!
            \param  player  current player.
        */
        void UndoAction(Player *player);
        Treasure takenTreasure; /*!< Treasure taken by player in current move. */
        bool stoneInserted;     /*!< True if stone was inserted this round. */
        bool playerMoved;       /*!< True if player has moved this round. */
        bool itemTaken;         /*!< True if treasure was taken this round. */
        Position previousInsert;        /*!< Position of last stone insertion do disable reverse insert. */
        Position previousPosition;      /*!< Previous position of player for undo action. */
        Position previousInsertTmp;     /*!< Previous position of last stone insertion for undo action. */
        Position treasurePosition;      /*!< Previous position of taken item for undo action. */
        bool isUndo;                    /*!< Bool value telling if player is returning his move to begining. */

    private:
        //! This function moves stones in given position.
        /*!
            \param  row     X position of stone insertion
            \param  column  Y position of stone insertion
            \param  where   enum specifying direction of insertion
            \return outgoing stone from opposite side
        */
        Stone MoveStones(int row, int column, Direction where);
        BoardSize boardSize;            /*!< Size of game board. */
        Stone **stones;                 /*!< Two dimensional array of stones, representing game board. */
        Stone freeStone;                /*!< Free stone out of game board. */
        std::vector<Stone*> visited;    /*!< Vector of already visited stones for path search algorithm. */
        int stonesL;                    /*!< Number of stones of type L. */
        int stonesT;                    /*!< Number of stones of type T. */
        int stonesI;                    /*!< Number of stones of type I. */
};

#endif // GAMEBOARD_H

/* End of file gameboard.h */