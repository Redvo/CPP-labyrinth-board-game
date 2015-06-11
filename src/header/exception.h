/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: exception.h
 * Description: This class extends default exceptions and proved custom messages and 
 *              error codes.
 ***************************************************************************************/

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "types.h"
#include <string>
#include <exception>

//! Class Exception
/*!
This class extends default exceptions and proved custom messages and 
error codes.
*/
class Exception
{

    public:
        //! Constructor of custom exception object.
        /*!
            \param  message     message of exception.
            \param  code        error code of exception.
        */
        Exception(std::string message, ErrorCode code);
        //! Destructor of custom exception object.
        virtual ~Exception();
        //! Getter for exception message.
        /*!
            \return exception message.
        */
        std::string GetMessage() noexcept;
        //! Getter for exception code.
        /*!
            \return exception code.
        */
        ErrorCode GetCode() noexcept;

    private:
        std::string message; /*!< Exception message. */
        ErrorCode code;      /*!< Exception code. */
};

//! Class WrongArgumentsException
/*!
This class extends default exceptions and proved custom messages and 
error codes.
*/
class WrongArgumentsException : public Exception
{
    public:
        //! Constructor of custom exception object.
        /*!
            \param  message     message of exception.
            \param  code        error code of exception.
        */
        WrongArgumentsException(std::string message, ErrorCode code);
        //! Destructor of custom exception object.
        virtual ~WrongArgumentsException();

};

//! Class StoneInsertException
/*!
This class extends default exceptions and proved custom messages and 
error codes.
*/
class StoneInsertException : public Exception
{
    public:
        //! Constructor of custom exception object.
        /*!
            \param  message     message of exception.
            \param  code        error code of exception.
        */
        StoneInsertException(std::string message, ErrorCode code);
        //! Destructor of custom exception object.
        virtual ~StoneInsertException();

};

//! Class InvalidFileException
/*!
This class extends default exceptions and proved custom messages and 
error codes.
*/
class InvalidFileException : public Exception
{
    public:
        //! Constructor of custom exception object.
        /*!
            \param  message     message of exception.
            \param  code        error code of exception.
        */
        InvalidFileException(std::string message, ErrorCode code);
        //! Destructor of custom exception object.
        virtual ~InvalidFileException();

};

//! Class AbsentPathException
/*!
This class extends default exceptions and proved custom messages and 
error codes.
*/
class AbsentPathException : public Exception
{
    public:
        //! Constructor of custom exception object.
        /*!
            \param  message     message of exception.
            \param  code        error code of exception.
        */
        AbsentPathException(std::string message, ErrorCode code);
        //! Destructor of custom exception object.
        ~AbsentPathException();
};

#endif // EXCEPTION_H

/* Enf of file exception.h */