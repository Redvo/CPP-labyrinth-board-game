/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: arguments.cpp
 * Description: Source code of functions defined in file arguments.h.
 ***************************************************************************************/

#include <arguments.h>

using namespace std;

Arguments::Arguments(int argCount, vector<string> arguments) {
    this->argCount = argCount;
    this->arguments = arguments;
    this->gameType = GameType::_GT_NOT_SET;
    this->playerCount = 2;
    this->boardSize = 7;
    this->cardCount = 12;
}

Arguments::~Arguments() {

}

int Arguments::GetArgumentsCount() noexcept {
    return this->argCount;
}

vector<string> Arguments::GetArguments() noexcept {
    return this->arguments;
}

void Arguments::ParseArguments() {

    string::size_type sz;
    bool pcset = false, bsset = false, ccset = false;
    string message;

    if(this->argCount == 0) {
        message = "Invalid arguments. Run with --help for detailed instructions.";
        throw new WrongArgumentsException(message, ErrorCode::_ERR_WRONG_ARGUMENT);
    }

    for(auto iterator = begin(this->arguments); iterator != end(this->arguments); ++iterator) {

        if((*iterator == "--help") && (this->gameType == GameType::_GT_NOT_SET)) {

            this->gameType = GameType::_GT_SHOW_HELP;

        } else if((*iterator == "--load") && (this->gameType == GameType::_GT_NOT_SET)) {

            this->gameType = GameType::_GT_LOAD;

        } else if((*iterator == "--new") && (this->gameType == GameType::_GT_NOT_SET)) {

            this->gameType = GameType::_GT_NEW;

        } else if((*iterator == "-p") && (this->gameType == GameType::_GT_NEW)) {

            if(pcset) {
                message = "Invalid arguments. Argument -p set multiple times."
                " Run with --help for detailed instructions.";
                throw new WrongArgumentsException(message, ErrorCode::_ERR_WRONG_ARGUMENT);
            }

            if(++iterator != end(this->arguments)) {

                try {
                    this->playerCount = stoi(*iterator,&sz);
                } catch (...) {
                    message = "Invalid arguments. Number of players (";
                    message += *iterator;
                    message += ") is not a number. Run with --help for detailed instructions.";
                    throw new WrongArgumentsException(message, ErrorCode::_ERR_WRONG_ARGUMENT);
                }

                if(sz != (*iterator).length()) {
                    message = "Invalid arguments. Number of players (";
                    message += *iterator;
                    message += ") is not a number. Run with --help for detailed instructions.";
                    throw new WrongArgumentsException(message, ErrorCode::_ERR_WRONG_ARGUMENT);
                }

                if(this->playerCount < 2 || this->playerCount > 4) {
                    message = "Invalid arguments. Number of players (";
                    message += *iterator;
                    message += ") must be between 2 and 4. Run with --help for detailed instructions.";
                    throw new WrongArgumentsException(message, ErrorCode::_ERR_WRONG_ARGUMENT);
                }

            } else {
                message = "Invalid arguments. Argument -p requires number of players."
                " Run with --help for detailed instructions.";
                throw new WrongArgumentsException(message, ErrorCode::_ERR_WRONG_ARGUMENT);
            }

        } else if((*iterator == "-c") && (this->gameType == GameType::_GT_NEW)) {

            if(ccset) {
                message = "Invalid arguments. Argument -c set multiple times."
                " Run with --help for detailed instructions.";
                throw new WrongArgumentsException(message, ErrorCode::_ERR_WRONG_ARGUMENT);
            }

            if(++iterator != end(this->arguments)) {

                try {
                    this->cardCount = stoi(*iterator,&sz);
                } catch (...) {
                    message = "Invalid arguments. Number of cards (";
                    message += *iterator;
                    message += ") is not a number. Run with --help for detailed instructions.";
                    throw new WrongArgumentsException(message, ErrorCode::_ERR_WRONG_ARGUMENT);
                }

                if(sz != (*iterator).length()) {
                    message = "Invalid arguments. Number of cards (";
                    message += *iterator;
                    message += ") is not a number. Run with --help for detailed instructions.";
                    throw new WrongArgumentsException(message, ErrorCode::_ERR_WRONG_ARGUMENT);
                }

                if(this->cardCount != 12 && this->cardCount != 24) {
                    message = "Invalid arguments. Number of cards (";
                    message += *iterator;
                    message += ") must be 12 or 24. Run with --help for detailed instructions.";
                    throw new WrongArgumentsException(message, ErrorCode::_ERR_WRONG_ARGUMENT);
                }

            } else {
                message = "Invalid arguments. Argument -c requires number of cards."
                " Run with --help for detailed instructions.";
                throw new WrongArgumentsException(message, ErrorCode::_ERR_WRONG_ARGUMENT);
            }

        } else if((*iterator == "-s") && (this->gameType == GameType::_GT_NEW)) {

            if(bsset) {
                message = "Invalid arguments. Argument -s set multiple times."
                " Run with --help for detailed instructions.";
                throw new WrongArgumentsException(message, ErrorCode::_ERR_WRONG_ARGUMENT);
            }

            if(++iterator != end(this->arguments)) {

                try {
                    this->boardSize = stoi(*iterator,&sz);
                } catch (...) {
                    message = "Invalid arguments. Number of players (";
                    message += *iterator;
                    message += ") is not a number. Run with --help for detailed instructions.";
                    throw new WrongArgumentsException(message, ErrorCode::_ERR_WRONG_ARGUMENT);
                }

                if(sz != (*iterator).length()) {
                    message = "Invalid arguments. Number of players (";
                    message += *iterator;
                    message += ") is not a number. Run with --help for detailed instructions.";
                    throw new WrongArgumentsException(message, ErrorCode::_ERR_WRONG_ARGUMENT);
                }

                if(this->boardSize != 5 && this->boardSize != 7 && this->boardSize != 9 && this->boardSize != 11) {
                    message = "Invalid arguments. Number of players (";
                    message += *iterator;
                    message += ") must be 5,7,9 or 11. Run with --help for detailed instructions.";
                    throw new WrongArgumentsException(message, ErrorCode::_ERR_WRONG_ARGUMENT);
                }

            } else {
                message = "Invalid arguments. Argument -p requires number of players."
                " Run with --help for detailed instructions.";
                throw new WrongArgumentsException(message, ErrorCode::_ERR_WRONG_ARGUMENT);
            }

        } else {
            string message = "Invalid argument ";
            message += *iterator;
            message += ". Run with --help for detailed instructions.";
            throw new WrongArgumentsException(message, ErrorCode::_ERR_WRONG_ARGUMENT);
        }

    }

}

GameType Arguments::GetGameType() noexcept {
    return this->gameType;
}

PlayerCount Arguments::GetPlayerCount() noexcept {
    return this->playerCount;
}

BoardSize Arguments::GetBoardSize() noexcept {
    return this->boardSize;
}

CardCount Arguments::GetCardCount() noexcept	 {
    return this->cardCount;
}

/* End of file arguments.cpp */