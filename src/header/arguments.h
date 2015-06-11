/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: arguments.h
 * Description: This class parses and validates arguments.
 ***************************************************************************************/

#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include "types.h"
#include "exception.h"
#include <string>
#include <vector>
#include <exception>

//! Class Arguments
/*!
This class parses and validates arguments.
*/
class Arguments
{
public:
    //! Constructor of arguments object.
    /*!
        \param  argConnt    number of arguments.
        \param  arguments   vector of arguments.
    */
    Arguments(int argCount, std::vector<std::string> arguments);
    //! Destructor of arguments object.
    ~Arguments();
    //! Getter for arguments count.
    /*!
        \return number of arguments.
    */
    int GetArgumentsCount() noexcept;
    //! Getter for arguments vector.
    /*!
        \return vector storing arguments.
    */
    std::vector<std::string> GetArguments() noexcept;
    //! Function parses arguments and throws exception on error.
    void ParseArguments();
    //! Function returns type of started game.
    /*!
        \return enum specifying type of game.
    */
    GameType GetGameType() noexcept;
    //! Getter for number of players specified in arguments. 
    /*!
        \return number of players.
    */
    PlayerCount GetPlayerCount() noexcept;
    //! Getter for size of game board specified in arguments. 
    /*!
        \return size of game board.
    */
    BoardSize GetBoardSize() noexcept;
    //! Getter for number of cards specified in arguments. 
    /*!
        \return number of cards.
    */
    CardCount GetCardCount() noexcept;

private:
    int argCount;
    std::vector<std::string> arguments; /*!< Vector of arguments. */
    PlayerCount playerCount; /*!< Number of players. */
    CardCount cardCount; /*!< Number of cards. */
    BoardSize boardSize; /*!< Size of game board. */
    GameType gameType; /*!< Type of game. */
};

#endif // ARGUMENTS_H

/* End of file arguments.h */