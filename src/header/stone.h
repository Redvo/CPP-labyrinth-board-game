/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: stone.h
 * Description: This header file contains class Stone which holds methods and 
 *              properties describing object of single stone on game board.
 ***************************************************************************************/

#ifndef STONE_H
#define STONE_H

#include <types.h>
#include <player.h>

//! Class Stone
/*!
This header file contains class Stone which holds methods and 
properties describing object of single stone on game board.
*/
class Stone
{
    public:
        //! Constructor of stone object.
        Stone();
        //! Destructor of stone object.
        ~Stone();
        //! Give type (look) and rotation to new stone.
        /*!
            \param  stoneType   The type of stone, defined by enum.
            \param  rotationType    Rotation of given stone, defined by enum.
            \sa     enum StoneType {}, enum StoneRotation{} in types.h.
        */
        void SetStone(StoneType stoneType, StoneRotation rotationType);
        //! Getter for type of stone.
        /*!
            \return Enum specifying type of this stone.
            \sa     enum StoneType {} in types.h.
        */
        StoneType GetStoneType();
        //! Setter for type of stone.
        /*!
            \param  type    Enum specifying type of stone.
            \sa     enum StoneRotation{} in types.h.
        */
        void SetStoneType(StoneType type);
        //! Getter for rotation of stone.
        /*!
            \return Enum specifying rotation of this stone.
            \sa     enum StoneRotation{} in types.h.
        */
        StoneRotation GetRotationType();
        //! Setter for rotation of stone.
        /*!
            \param  rotation    Enum specifying rotation of this stone.
            \sa     enum StoneRotation{} in types.h.
        */
        void SetRotationType(StoneRotation rotation);
        //! Getter for existing paths in stone.
        /*!
            \return Structure with members representing paths.
            \sa     struct Paths {} in types.h.
        */
        Paths GetPaths();
        //! Function rotates stone by 90 degrees clockwise.
        void Rotate();
        //! Function adds player on this stone.
        /*!
            \param  player  Player object which will be add on this stone.
            \sa     SetPlayers().
        */
        void AddPlayer(Player *player);
        //! Function adds players on this stone.
        /*!
            \param  players  Vector of all players which will be add on this stone.
            \sa     AddPlayer().
        */
        void SetPlayers(std::vector<Player*> players);
        //! Function removes player from this stone.
        /*!
            \param  playerId  Numeric identificator of player, which will be removed.
            \sa     RemovePlayers().
        */
        void RemovePlayer(int playerId);
        //! Function removes all players from this stone.
        /*!
            \sa     RemovePlayer().
        */
        void RemovePlayers();
        //! Getter for vector of all players on this stone.
        /*!
            \return Vector of players on this stone.
            \sa     RemovePlayer().
        */
        std::vector<Player*> GetPlayers();
        //! Getter for player object identified by its identificator.
        /*!
            \param  playerId  Numeric identificator of player, whose object we want to get.
            \return Player object if exists or null if not.
            \sa     RemovePlayers().
        */
        Player *GetPlayer(int playerId);
        //! Function checks if there is any player on this stone.
        /*!
            \return True if any player is on this stone, false otherwise.
        */
        bool HasPlayer();
        //! Getter for treasure numeric identificator.
        /*!
            \return Treasures numeric identificator or 0 if stone has no treasure.
        */
        Treasure GetTreasure();
        //! Setter for vector of all players on this stone.
        /*!
            \param  treasure    Numeric identificator of treasure, which will be add on this stone.
        */
        void SetTreasure(Treasure treasure);

    private:

        StoneType stoneType; /*!< Enum specifying type of this stone. */
        StoneRotation actualRotationType; /*!< Enum specifying rotation of this stone. */
        Treasure treasure; /*!< Numeric identificator of treasure. */ 
        Paths freePaths; /*!< Structure specifying free paths on this stone. */ 
        std::vector<Player*> players; /*!< Vector of all players on this stone. */ 
        bool hasPlayer; /*!< Boolean value telling if this stone has any player. */ 
};

#endif // STONE_H

/* End of file stone.h */