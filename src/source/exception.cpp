/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: exception.cpp
 * Description: Source code of functions defined in file exception.h.
 ***************************************************************************************/

#include <exception.h>

using namespace std;

Exception::Exception(string message, ErrorCode code)	 {
    this->message = message;
    this->code = code;
}

Exception::~Exception() {

}

std::string Exception::GetMessage() noexcept {
    return this->message;
}

ErrorCode Exception::GetCode() noexcept {
    return this->code;
}

WrongArgumentsException::WrongArgumentsException(string message, ErrorCode code) :
    Exception(message, code) {

}

WrongArgumentsException::~WrongArgumentsException() {

}

StoneInsertException::StoneInsertException(string message, ErrorCode code) :
    Exception(message, code) {

}

StoneInsertException::~StoneInsertException() {

}


InvalidFileException::InvalidFileException(string message, ErrorCode code) :
    Exception(message, code) {

}

InvalidFileException::~InvalidFileException() {

}

AbsentPathException::AbsentPathException(string message, ErrorCode code) :
    Exception(message, code) {

}

AbsentPathException::~AbsentPathException() {

}

/* End of file exception.cpp */