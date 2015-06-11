/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: main.cpp
 * Description: Main file of CLI based Labyrinth board game.
 ***************************************************************************************/

#include <types.h>
#include <exception.h>
#include <arguments.h>
#include <playerlist.h>
#include <player.h>
#include <game.h>
#include <gameboard.h>
#include <cardpack.h>
#include <treasurecard.h>
#include <holdingtreasure.h>

#include <string>
#include <cstring>
#include <iostream>

using namespace std;

string usageMessage = "\n\
THE LABYRINTH BOARD GAME\n\
Authors: Irena Talašová   [xtalas04@stud.fit.vutbr.cz]\n\
         Lukáš Rendvanský [xrendv00@stud.fit.vutbr.cz]\n\
Details: This project in course The C++ Programming Language is program implementation of board game The Labyrinth.\n\n\
Usage: ./labyrinth --help | --load | --new [-p players] [-s size] [-c cards]\n\
  --help      Prints this help message.\n\
  --load      Load game that has been previously saved.\n\
  --new       Starts new game. Additional parameters can be specified:\n\
  -p players  Number of players in new game. Default = 2.\n\
  -s size     Size of game board. Can take values 5, 7, 9, 11. Default = 7.\n\
  -c cards    Number of total cards redistributed to each player. Can take values 12 or 24. Default = 12.\n";

string helpMessage = "Commands:\n\
help     - Prints this help.\n\
board    - Prints game board layout.\n\
card     - Prints actual card on hand.\n\
stone    - Prints actual free stone.\n\
rotate   - Rotate stone and print it.\n\
achieved - Prints achieved cards of all players.\n\
insert   - Insert stone.\n\
move     - Move player.\n\
end      - End turn.\n\
save     - Save game.\n\
exit     - Exit game.\n";

void Play(Game *game);
void PrintCards(Game *game);
void PrintAchievedCards(Game *game);
void PrintBoard(Game *game);
void PrintFreeStone(Game *game);
void PlayerActions(Game *game);

int main(int argc, char** argv) {

    PlayerCount playerCount = 2;
    CardCount cardCount = 12;
    BoardSize boardSize = 7;
    GameType gameType = GameType::_GT_NOT_SET;
    vector<string> argvec;
    Arguments *arguments = NULL;
    Game *game = NULL;

    srand(time(0));

    argvec.insert(end(argvec), argv+1, argv+argc);
    arguments = new Arguments(argc - 1, argvec);

    try {
        arguments->ParseArguments();
    } catch(WrongArgumentsException *ex) {
        cerr << ex->GetMessage() << endl;
        exit(ex->GetCode());
    }

    playerCount = arguments->GetPlayerCount();
    cardCount = arguments->GetCardCount();
    boardSize = arguments->GetBoardSize();
    gameType = arguments->GetGameType();

    switch(gameType) {
        case GameType::_GT_NEW: {
            game = Game::NewGame(boardSize, cardCount, playerCount);
        } break;
        case GameType::_GT_LOAD: {
            string saveName;
            cout << "Name of the game: ";
            cin >> saveName;
            try {
                game = Game::LoadGame(saveName);
                game->SetPlayersOnBoard();
                HoldingTreasure::cards = cardCount;
                HoldingTreasure::players = playerCount;
            } catch (InvalidFileException *ex) {
                cerr << ex->GetMessage() << endl;
                exit(ex->GetCode());
            }
        } break;
        case GameType::_GT_SHOW_HELP: {
            cout << usageMessage << endl;
            exit(0);
        }
        case GameType::_GT_NOT_SET:
        default: {
            cerr << "Unknown error occured." << endl;
            exit(ErrorCode::_ERR_UNKNOWN);
        }

    }

    cout << "Game started!!!" << endl;
    cout << "Number of players: " << to_string(game->GetPlayerCount()) << endl;
    cout << "Board size: " << to_string(game->GetBoardSize()) << "x" << to_string(game->GetBoardSize()) << endl;
    cout << "Card pack size: " << to_string(game->GetPackSize()) << endl;

    Play(game);

    return 0;

}

void Play(Game *game) {

    Player *currentPlayer = NULL;

    cout << "GAME STARTED! Good luck and have fun." << endl;

    while(1) {
        PrintBoard(game);
        PrintFreeStone(game);

        currentPlayer = game->GetCurrentPlayer();

        cout << "\033[3" << currentPlayer->GetPlayerId() <<
                "mPlayer " << currentPlayer->GetPlayerId() <<
                " turn.\033[0m" << endl;

        if(currentPlayer->GetTreasureCard() == NULL) {
            cout << "No cards on hand. Taking new card." << endl;
            currentPlayer->SetTreasureCard(game->PopCard());
        }

        PrintCards(game);

        PlayerActions(game);

        game->NextPlayer();
    }

    game->DeleteStones();

    return;

}

void PlayerActions(Game *game) {

    string command;
    Player *currentPlayer = game->GetCurrentPlayer();

    while(1) {
        cout << "Enter command (enter \"help\" if you need help): ";
        cin >> command;
        if(command == "help") {
            cout << helpMessage << endl << endl;
        } else if (command == "turn") {
            cout << endl << "\033[3" << to_string(currentPlayer->GetPlayerId()) << "m"
                 << "Player " << to_string(currentPlayer->GetPlayerId()) << " turn.\033[0m "
                 << endl<< endl;
        } else if (command == "board") {
            PrintBoard(game);
        } else if (command == "card") {
            PrintCards(game);
        } else if (command == "stone") {
            cout << endl;
            PrintFreeStone(game);
        } else if (command == "rotate") {

            if(game->stoneInserted) {
                cout << "You have already inserted the stone!" << endl;
                continue;
            }

            cout << endl << "\033[35mROTATING STONE.\033[0m" << endl << endl;
            game->GetFreeStone()->Rotate();
            PrintFreeStone(game);
        } else if (command == "achieved") {
            PrintAchievedCards(game);
        } else if (command == "insert") {
            string where, val;
            string::size_type sz;
            int x, y;

            if(game->stoneInserted) {
                cout << "You have already inserted the stone!" << endl;
                continue;
            }

            while (1) {
                cout << "Set side of stone insertion : T - top, R - right, B - bottom, L - left, Q - back: ";
                cin >> where;
                if(where == "T" || where == "t") {
                    x = 0;
                    while(1) {
                        cout << "Enter column number from values";
                        for (int i = 0; i < game->GetBoardSize(); i++) {
                            if(i % 2 == 1) {
                                cout << " " << to_string(i + 1);
                            }
                        }
                        cout << " or Q to exit: ";
                        cin >> val;

                        if(val == "Q" || val == "q") {
                            break;
                        }

                        try {
                            y = stoi (val,&sz);
                        } catch (...) {
                            cout << "Error - bad value." << endl;
                            continue;
                        }

                        if(sz != val.length()) {
                            cout << "Error - bad value." << endl;
                            continue;
                        }

                        try {
                            game->AddStone(x, y - 1);
                        } catch (StoneInsertException *ex) {
                            cout << ex->GetMessage() << endl;
                            continue;
                        }

                        cout << "Stone inserted." << endl;
                        game->stoneInserted = true;
                        break;

                    }
                    break;
                } else if(where == "R" || where == "r") {
                    y = game->GetBoardSize() - 1;
                    while(1) {
                        cout << "Enter row number from values";
                        for (int i = 0; i < game->GetBoardSize(); i++) {
                            if(i % 2 == 1) {
                                cout << " " << to_string(i + 1);
                            }
                        }
                        cout << " or Q to exit: ";
                        cin >> val;

                        if(val == "Q" || val == "q") {
                            break;
                        }

                        try {
                            x = stoi (val,&sz);
                        } catch (...) {
                            cout << "Error - bad value." << endl;
                            continue;
                        }

                        if(sz != val.length()) {
                            cout << "Error - bad value." << endl;
                            continue;
                        }

                        try {
                            game->AddStone(x - 1, y);
                        } catch (StoneInsertException *ex) {
                            cout << ex->GetMessage() << endl;
                            continue;
                        }

                        cout << "Stone inserted." << endl;
                        game->stoneInserted = true;
                        break;

                    }
                    break;
                } else if(where == "B" || where == "b") {
                    x = game->GetBoardSize() - 1;
                    while(1) {
                        cout << "Enter column number from values";
                        for (int i = 0; i < game->GetBoardSize(); i++) {
                            if(i % 2 == 1) {
                                cout << " " << to_string(i + 1);
                            }
                        }
                        cout << " or Q to exit: ";
                        cin >> val;

                        if(val == "Q" || val == "q") {
                            break;
                        }

                        try {
                            y = stoi (val,&sz);
                        } catch (...) {
                            cout << "Error - bad value." << endl;
                            continue;
                        }

                        if(sz != val.length()) {
                            cout << "Error - bad value." << endl;
                            continue;
                        }

                        try {
                            game->AddStone(x, y - 1);
                        } catch (StoneInsertException *ex) {
                            cout << ex->GetMessage() << endl;
                            continue;
                        }

                        cout << "Stone inserted." << endl;
                        game->stoneInserted = true;
                        break;
                    }
                    break;
                } else if(where == "L" || where == "l") {
                    y = 0;
                    while(1) {
                        cout << "Enter row number from values";
                        for (int i = 0; i < game->GetBoardSize(); i++) {
                            if(i % 2 == 1) {
                                cout << " " << to_string(i + 1);
                            }
                        }
                        cout << " or Q to exit: ";
                        cin >> val;

                        if(val == "Q" || val == "q") {
                            break;
                        }

                        try {
                            x = stoi (val,&sz);
                        } catch (...) {
                            cout << "Error - bad value." << endl;
                            continue;
                        }

                        if(sz != val.length()) {
                            cout << "Error - bad value." << endl;
                            continue;
                        }

                        try {
                            game->AddStone(x - 1, y);
                        } catch (StoneInsertException *ex) {
                            cout << ex->GetMessage() << endl;
                            continue;
                        }

                        cout << "Stone inserted." << endl;
                        game->stoneInserted = true;
                        break;
                    }
                    break;
                } else if(where == "Q" || where == "q") {
                    break;
                }
            }
        } else if (command == "move") {

            if(!game->stoneInserted) {
                cout << "You have to insert stone before moving!" << endl;
                continue;
            }

            if(game->playerMoved) {
                cout << "You have already moved!" << endl;
                continue;
            }

            while(1) {
                cout << "Enter number of row and column separated by space, or Q to exit: ";
                getline(cin, command);
                if(command == "Q" || command == "q") {
                    break;
                } else {

                    string xPos, yPos;
                    int xCoor, yCoor;
                    size_t find;
                    string::size_type sz;

                    if(command.empty()) {
                        cout << "Error - bad value." << endl;
                        continue;
                    }

                    find = command.find(' ');
                    if(find == command.npos) {
                        cout << "Error - bad value." << endl;
                        continue;
                    }

                    xPos = command.substr(0,find);
                    yPos = command.substr(find, command.npos - find);

                    if(xPos.empty() || yPos.empty()) {
                        cout << "Error - bad value." << endl;
                        continue;
                    }

                    try {
                        xCoor = stoi (xPos,&sz);
                    } catch (...) {
                        cout << "Error - bad value." << endl;
                        continue;
                    }

                    if(sz != xPos.length()) {
                        cout << "Error - bad value." << endl;
                        continue;
                    }

                    try {
                        yCoor = stoi (yPos,&sz);
                    } catch (...) {
                        cout << "Error - bad value." << endl;
                        continue;
                    }

                    if(sz != yPos.length()) {
                        cout << "Error - bad value." << endl;
                        continue;
                    }

                    if((xCoor < 1) || (xCoor > game->GetBoardSize()) ||
                            (yCoor < 1) || (yCoor > game->GetBoardSize())) {
                        cout << "Error - bad value." << endl;
                        continue;
                    }

                    try {
                        game->MovePlayer(currentPlayer, xCoor - 1, yCoor - 1);

                        if(game->GetCurrentPlayer()->GetHoldingTreasure()->CheckForVictory()) {
                            cout << "\033[3" << to_string(currentPlayer->GetPlayerId()) << "mPlayer " <<
                                    to_string(currentPlayer->GetPlayerId()) << " won the game! Congratulations!!!\033[0m" <<
                                    endl << endl;
                            PrintAchievedCards(game);
                            exit(0);
                        }

                        game->playerMoved = true;
                        break;

                    } catch (AbsentPathException *ex) {
                        cout << ex->GetMessage() << endl;
                        continue;
                    }

                }

            }
        }else if (command == "end") {
            if(!game->stoneInserted) {
                cout << "You have to insert stone and move before ending your turn!" << endl;
                continue;
            }

            game->stoneInserted = false;
            game->playerMoved = false;

            return;


        } else if (command == "save") {
            string filename;
            cout << "Enter file name: ";
            cin >> filename;
            if(!filename.empty()) {
                try {
                    game->SaveGame(filename);
                } catch(InvalidFileException *ex) {
                    cout << ex->GetMessage() << endl;
                }
            }
            continue;

        } else if (command == "exit") {
            exit (0);
        } else {
            cout << "Bad command (enter \"help\" if you need help)." << endl;
        }

    }

}

void PrintCards(Game *game) {

    cout << endl;
    for(Player *player : game->GetPlayerList()) {
        cout << "\033[3" << to_string(player->GetPlayerId()) << "m"<<
                "Player " << to_string(player->GetPlayerId()) << " card:\033[0m ";
        if(player->GetTreasureCard() != NULL) {
            if(player->GetPlayerId() == game->GetCurrentPlayer()->GetPlayerId()) {
                cout << "\033[36m" << static_cast<char>(player->GetTreasureCard()->GetCardNumber() + 'A' - 1) << "\033[0m";
            } else {
                cout << "Not your turn.";
            }
        } else {
            cout << "No card on hand.";
        }
        cout << endl;
    }
    cout << endl;

}

void PrintAchievedCards(Game *game) {

    for(Player *player : game->GetPlayerList()) {
        cout << "\033[3" << to_string(player->GetPlayerId()) << "m"<<
                "Player " << to_string(player->GetPlayerId()) << " achieved cards:\033[0m";
        if(player->GetHoldingTreasure()->GetAchievedCards()->empty()) {
            cout << "No achieved cards.";
        } else {
            cout << "\033[36m";
            for(auto card : *(player->GetHoldingTreasure()->GetAchievedCards())) {
                cout << static_cast<char>(card->GetCardNumber() + 'A' - 1) << " ";
            }
            cout << "\033[0m";
        }
        cout << endl;
    }
    cout << endl;

}

void PrintBoard(Game *game) {

    cout << endl;
    cout << "**************************************" << endl;
    cout << "********** LABYRINTH LAYOUT **********" << endl;
    cout << "**************************************" << endl << endl;
    int i, j;
    Stone *stone;
    vector<Player*> players;

    cout << "#";
    for(j = 0; j < game->GetBoardSize(); j++) {
        if(j%2 == 1) {
            for(int i = 0; i < game->GetPlayerCount(); i++) {
                cout << "#";
            }
            cout << "■##";
        }
        else {
            for(int i = 0; i < game->GetPlayerCount(); i++) {
                cout << "#";
            }
            cout << "###";
        }
    }
    cout << endl;

    for(i = 0; i < game->GetBoardSize(); i++) {
        if(i%2 == 1)
            cout << "■";
        else
            cout << "#";
        for(j = 0; j < game->GetBoardSize(); j++) {
            stone = game->GetStone(i,j);
            players = stone->GetPlayers();
            if(stone->HasPlayer()) {
                for(Player *player : players) {
                    cout << "\033[3" << player->GetPlayerId() << "m" << player->GetPlayerId() << "\033[0m";
                }
                for(int pcount = stone->GetPlayers().size(); pcount < game->GetPlayerCount(); pcount++) {
                    cout << " ";
                }
            } else {
                for(int i = 0; i < game->GetPlayerCount(); i++) {
                    cout << " ";
                }
            }

            switch(stone->GetStoneType()) {
                case StoneType::_ST_L: {
                    switch(stone->GetRotationType()) {
                        case StoneRotation::_SR_T: {
                            cout << "\033[35m╚\033[0m";
                        } break;
                        case StoneRotation::_SR_L: {
                            cout << "\033[35m╝\033[0m";
                        } break;
                        case StoneRotation::_SR_B: {
                            cout << "\033[35m╗\033[0m";
                        } break;
                        case StoneRotation::_SR_R: {
                            cout << "\033[35m╔\033[0m";
                        } break;
                    }
                } break;
                case  StoneType::_ST_T: {
                    switch(stone->GetRotationType()) {
                        case StoneRotation::_SR_T: {
                            cout << "\033[35m╦\033[0m";
                        } break;
                        case StoneRotation::_SR_L: {
                            cout << "\033[35m╠\033[0m";
                        } break;
                        case StoneRotation::_SR_B: {
                            cout << "\033[35m╩\033[0m";
                        } break;
                        case StoneRotation::_SR_R: {
                            cout << "\033[35m╣\033[0m";
                        } break;
                    }
                } break;
                case StoneType::_ST_I: {
                    switch(stone->GetRotationType()) {
                        case StoneRotation::_SR_T:
                        case StoneRotation::_SR_B:{
                            cout << "\033[35m║\033[0m";
                        } break;
                        case StoneRotation::_SR_L:
                        case StoneRotation::_SR_R:{
                            cout << "\033[35m═\033[0m";
                        } break;
                    }
                } break;
            }

            if(stone->GetTreasure() != 0) {
                cout << "\033[36m" << static_cast<char>(stone->GetTreasure() + 'A' - 1) << "\033[0m";
            } else {
                cout << " ";
            }
            if(i%2 == 1 && j == game->GetBoardSize() - 1)
                cout << "■";
            else
                cout << "#";
        }
        cout << endl << "#";
        for(j = 0; j < game->GetBoardSize(); j++) {
            if(j%2 == 1 && i == game->GetBoardSize() - 1) {
                for(int i = 0; i < game->GetPlayerCount(); i++) {
                    cout << "#";
                }
                cout << "■##";
            }
            else {
                for(int i = 0; i < game->GetPlayerCount(); i++) {
                    cout << "#";
                }
                cout << "###";
            }
        }
        cout << endl;

    }

    cout << endl;

}

void PrintFreeStone(Game *game) {
    Stone *stone;
    cout << "            ###" << endl;
    cout << "Free stone: #\033[35m";
    stone = game->GetFreeStone();

    switch(stone->GetStoneType()) {
        case StoneType::_ST_L: {
            switch(stone->GetRotationType()) {
                case StoneRotation::_SR_T: {
                    cout << "╚";
                } break;
                case StoneRotation::_SR_L: {
                    cout << "╝";
                } break;
                case StoneRotation::_SR_B: {
                    cout << "╗";
                } break;
                case StoneRotation::_SR_R: {
                    cout << "╔";
                } break;
            }
        } break;
        case  StoneType::_ST_T: {
            switch(stone->GetRotationType()) {
                case StoneRotation::_SR_T: {
                    cout << "╦";
                } break;
                case StoneRotation::_SR_L: {
                    cout << "╠";
                } break;
                case StoneRotation::_SR_B: {
                    cout << "╩";
                } break;
                case StoneRotation::_SR_R: {
                    cout << "╣";
                } break;
            }
        } break;
        case StoneType::_ST_I: {
            switch(stone->GetRotationType()) {
                case StoneRotation::_SR_T:
                case StoneRotation::_SR_B:{
                    cout << "║";
                } break;
                case StoneRotation::_SR_L:
                case StoneRotation::_SR_R:{
                    cout << "═";
                } break;
            }
        } break;
    }
    cout << "\033[0m#" << endl;
    cout << "            ###" << endl << endl;
}
