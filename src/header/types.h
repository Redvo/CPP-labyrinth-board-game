/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: types.h
 * Description: This header file contains all general data types used in project.
 ***************************************************************************************/

#ifndef TYPES
#define TYPES

typedef unsigned char PlayerCount; /**< Number of players. */
typedef unsigned char CardCount;   /**< Number of cards. */
typedef unsigned char BoardSize;   /**< Size of game boards. */
typedef unsigned char Treasure;    /**< Identificator of treasure. */

//! Enum GameType.
/*! This enumeration specifies type of created game. */
typedef enum GameType{
    _GT_NOT_SET = 0,   /*!< No game type has been set. */ 
    _GT_NEW = 1,       /*!< New game created. */ 
    _GT_LOAD = 2,      /*!< Loaded game created. */ 
    _GT_SHOW_HELP = 3, /*!< Game help requested. */ 
} GameType;

//! Enum ErrorCode.
/*! This enumeration specifies error code in throw expressions. */
typedef enum ErrorCode {
    _ERR_WRONG_ARGUMENT = 90, /*!< Error for invalid arguments. */ 
    _ERR_UNKNOWN = 99         /*!< Unknown error. */ 
} ErrorCode;

//! Struct PlayerPosition.
/*! This structure holds X and Y coordinates of player on game board. */
typedef struct PlayerPosition {
    int xPosition; /*!< Players X position. */ 
    int yPosition; /*!< Players Y position. */ 
} Position;

//! Enum Direction.
/*! This enumeration specifies direction of stione insertion. */
typedef enum Direction {
    _DIR_UP = 0,   /*!< Direction from bottom to top. */ 
    _DIR_DOWN = 1, /*!< Direction from top to bottom. */ 
    _DIR_LEFT = 2, /*!< Direction from right to left. */ 
    _DIR_RIGHT = 3 /*!< Direction from left to right. */ 
} Direction;

//! Enum StoneType.
/*! This enumeration specifies type (look) of stone. */
typedef enum StoneType {
    _ST_L = 0, /*!< Stone of type L. */ 
    _ST_T = 1, /*!< Stone of type T. */ 
    _ST_I = 2  /*!< Stone of type I. */ 
} StoneType;

//! Enum StoneRotation.
/*! This enum specifies rotation of stone. */
typedef enum StoneRotation {
    _SR_T = 0, /*!< Base stone rotated by 0 degrees. */ 
    _SR_R = 1, /*!< Base stone rotated by 90 degrees. */ 
    _SR_B = 2, /*!< Base stone rotated by 180 degrees. */ 
    _SR_L = 3  /*!< Base stone rotated by 270 degrees. */ 
} StoneRotation;

//! Struct Paths.
/*! This enum specifies on which side of stone path exists */
typedef struct Paths {
    char TOP;    /*!< Path on top size of stone. */ 
    char RIGHT;  /*!< Path on right size of stone. */ 
    char BOTTOM; /*!< Path on bottom size of stone. */ 
    char LEFT;   /*!< Path on left size of stone. */ 
} Paths;

#endif // TYPES

/* End of file types.h */