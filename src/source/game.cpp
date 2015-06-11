/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: game.cpp
 * Description: Source code of functions defined in file game.h.
 ***************************************************************************************/

#include <game.h>

using namespace std;

Game::Game(BoardSize boardSize, CardCount cardCount, PlayerCount playerCount)
    : CardPack(cardCount), GameBoard(boardSize), PlayerList(playerCount, boardSize)
{
	this->boardSize = boardSize;
	this->cardCount = cardCount;
    this->playerCount = playerCount;
}

Game::~Game() {

}

BoardSize Game::GetBoardSize() {
    return this->boardSize;
}

CardCount Game::GetPackSize() {
    return this->cardCount;
}

PlayerCount Game::GetPlayerCount() {
    return this->playerCount;
}

void Game::SetPlayersOnBoard() {
	Stone *stone = NULL;
	for(Player *player : this->GetPlayerList()) {
       stone = this->GetStone(player->GetPosition().xPosition, player->GetPosition().yPosition);
       if(!stone->HasPlayer())
       stone->AddPlayer(player);
    }
}

void Game::SaveGame(string filename) {
	string line;
	ofstream myfile;
	Stone *stone;

	try {

		myfile.open (filename, ios::out | ios::trunc | ios::binary);

		// Game board settings
		// BOARD_SIZE:PLAYER_COUNT:CARD_COUNT
		myfile << to_string(this->boardSize) << ":" << to_string(this->playerCount) << ":" << to_string(this->cardCount) << endl;

		// Player on move
		// CURRENT_PLAYER_ID
		for(Player *player : this->GetPlayerList()) { 
			if(player == this->GetCurrentPlayer()) {
				myfile << to_string(player->GetPlayerId()) << endl; 
			}
		}

		// Players settings
		// PLAYER_ID:PLAYER_X:PLAYER_Y:PLAYER_TREASURECARD#PLAYER_ACHIEVEDCARDS[card: ...]
		for(Player *player : this->GetPlayerList()) {
			myfile <<
			to_string(player->GetPlayerId()) << ":" << 
			to_string(player->GetPosition().xPosition) << ":" << 
			to_string(player->GetPosition().yPosition) << ":";
			if(player->GetTreasureCard() != NULL) {
				myfile << to_string(player->GetTreasureCard()->GetCardNumber());
			} else {
				myfile << to_string(0);
			}

			myfile << "#";
            for(auto treasureCard : *(player->GetHoldingTreasure()->GetAchievedCards())) {
				myfile << to_string(treasureCard->GetCardNumber());
                if(treasureCard != player->GetHoldingTreasure()->GetAchievedCards()->back()) {
					myfile << ":";
				}
			}
			myfile << endl;
		}

		// Free stone
		// STONE_TYPE:STONE_ROTATION
		myfile << to_string(this->GetFreeStone()->GetStoneType()) << ":" << to_string(this->GetFreeStone()->GetRotationType()) << endl;

		// Stones cnfiguration
		// STONE_X:STONE_Y:STONE_TYPE:STONE_ROTATION:STONE_TREASURE#STONE_PLAYERS[player: ...]
		for(int i = 0; i < this->boardSize; i++) {
			for(int j = 0; j < this->boardSize; j++) {
				myfile << to_string(i) << ":" << to_string(j) << ":";
				stone = this->GetStone(i, j);
				myfile << to_string(stone->GetStoneType()) << ":" <<
				to_string(stone->GetRotationType()) << ":" <<
				to_string(stone->GetTreasure()); /* << "#";

				for(auto player : stone->GetPlayers()) {
					myfile << to_string(player->GetPlayerId());
					if(player != stone->GetPlayers().back()) {
						myfile << ":";
					}


				}*/

				myfile << endl;


			}
		}

		// Card pack
		// TREASURE_CARD_ID
		for(TreasureCard *card : this->GetCardPack()) { 
			myfile << to_string(card->GetCardNumber());
			if(card != this->GetCardPack().back()) {
				myfile << ":";
			}
		}

		myfile << endl;

		// MovementValues
		// TAKEN_TREASURE:STONE_INSERTED:PLAYER_MOVED:ITEM_TAKEN
		myfile << to_string(this->takenTreasure) << ":";

		if(this->playerMoved) {
			myfile << "1:";
		} else {
			myfile << "0:";
		}

		if(this->stoneInserted) {
			myfile << "1:";
		} else {
			myfile << "0:";
		}

		if(this->itemTaken) {
			myfile << "1";
		} else {
			myfile << "0";
		}

		myfile << endl;

		// Previous values
		// PREV_INS_X:PREV_INS_Y:PREV_TMPINS_X:PREV_TMPINS_Y:PREV_POS_X:PREV_POS_Y
	    myfile << to_string(this->previousInsert.xPosition) << ":";
	    myfile << to_string(this->previousInsert.yPosition) << ":";
	    myfile << to_string(this->previousInsertTmp.xPosition) << ":";
	    myfile << to_string(this->previousInsertTmp.yPosition) << ":";
	    myfile << to_string(this->previousPosition.xPosition) << ":";
	    myfile << to_string(this->previousPosition.yPosition);

		myfile << endl;

		myfile.close();

	} catch (...) {
		throw InvalidFileException("Invalid file.", ErrorCode::_ERR_UNKNOWN);
	}
} 

vector<string> Game::StringSplit(string str, char delimiter) {
	vector<string> elements;
    stringstream ss(str);
    string item;
    while (std::getline(ss, item, delimiter)) {
        elements.push_back(item);
    }
    return elements;
}

Game *Game::LoadGame(string filename) {

	string line, playerPartOne, playerPartTwo, stonePartOne, stonePartTwo;
	ifstream myfile;
	vector<string> lineValues, parts;
	HoldingTreasure *treasure = NULL;
	Game *game = NULL;
	Player *player = NULL;
	int boardSize, playerCount, cardCount;
	int playerId, treasureCard, currPlayerId;
	int stoneX, stoneY, stoneType, stoneRotation, stoneTreasure;
	Position position;
	Stone *stone = NULL;
	Stone freeStone;

	try {

		myfile.open (filename, ios::in | ios::binary);

		getline(myfile, line);

		lineValues = StringSplit(line, ':'); // BOARD_SIZE:PLAYER_COUNT:CARD_COUNT
		boardSize = stoi(lineValues.at(0));
		playerCount = stoi(lineValues.at(1));
		cardCount = stoi(lineValues.at(2));

		game = new Game(boardSize, cardCount, playerCount);
	
		getline(myfile, line);
		currPlayerId = stoi(line); // CURRENT_PLAYER_ID

		for(int i = 0; i < playerCount; i++) {
			getline(myfile, line);
			parts = StringSplit(line, '#');
			playerPartOne = parts.at(0); // PLAYER_ID:PLAYER_X:PLAYER_Y:PLAYER_TREASURECARD
			lineValues = StringSplit(playerPartOne, ':');
			playerId = stoi(lineValues.at(0));
			position.xPosition = stoi(lineValues.at(1));
			position.yPosition = stoi(lineValues.at(2));
			treasureCard = stoi(lineValues.at(3));
			treasure = new HoldingTreasure();

			if(parts.at(0) != parts.back()) {
				playerPartTwo = parts.at(1); // PLAYER_ACHIEVEDCARDS[card: ...]
				lineValues = StringSplit(playerPartTwo, ':');
				if(!lineValues.empty()) {
					for(string t : lineValues) {
						treasure->AchieveCard(new TreasureCard(static_cast<Treasure>(stoi(t))));
					}
				}
			}

			player = new Player(position, treasure, playerId);
			if(treasureCard == 0) {
				player->SetTreasureCard(NULL);
			} else {
				player->SetTreasureCard(new TreasureCard(static_cast<Treasure>(treasureCard)));
			}
			game->AddPlayer(player);

			if(playerId == currPlayerId) {
				game->SetCurrentPlayer(player);
			}

		}


		getline(myfile, line);
		parts = StringSplit(line, ':'); // STONE_TYPE:STONE_ROTATION
		freeStone = Stone();
        freeStone.SetStone(static_cast<StoneType>(stoi(parts.at(0))),static_cast<StoneRotation>(stoi(parts.at(1))));
		game->SetFreeStone(freeStone);

		game->CreateStones();

		for(int i = 0; i < boardSize * boardSize; i++) {
			getline(myfile, line);
			//parts = StringSplit(line, '#');
			//stonePartOne = parts.at(0); // PLAYER_ID:PLAYER_X:PLAYER_Y:PLAYER_TREASURECARD
			lineValues = StringSplit(line, ':'); // STONE_X:STONE_Y:STONE_TYPE:STONE_ROTATION:STONE_TREASURE
			stoneX = stoi(lineValues.at(0));
			stoneY = stoi(lineValues.at(1));
			stoneType = stoi(lineValues.at(2));
			stoneRotation = stoi(lineValues.at(3)); 
			stoneTreasure = stoi(lineValues.at(4));
			stone = game->GetStone(stoneX, stoneY);
			stone->SetStone(static_cast<StoneType>(stoneType), static_cast<StoneRotation>(stoneRotation));
			stone->SetTreasure(static_cast<Treasure>(stoneTreasure));
			/*if(parts.at(0) != parts.back()) {
				stonePartTwo = parts.at(1); // PLAYER_ACHIEVEDCARDS[card: ...]
				lineValues = StringSplit(stonePartTwo, ':');
				if(!lineValues.empty()) {
					for(string t : lineValues) {
						player = game->FindPlayer(stoi(t));
						//stone->AddPlayer(player);
					}
				}
			}*/

		}

		getline(myfile, line);
		parts = StringSplit(line, ':'); // STONE_TYPE:STONE_ROTATION
		for(string sp : parts) {
			game->AddToCardPack(new TreasureCard(static_cast<Treasure>(stoi(sp))));
		}

		getline(myfile, line);
		parts = StringSplit(line, ':'); // TAKEN_TREASURE:STONE_INSERTED:PLAYER_MOVED:ITEM_TAKEN:IS_UNDO
		game->takenTreasure = stoi(parts.at(0));
		if(parts.at(1) == "1") {
			game->playerMoved = true;
		} else {
			game->playerMoved = false;
		}

		if(parts.at(2) == "1") {
			game->stoneInserted = true;
		} else {
			game->stoneInserted = false;
		}

		if(parts.at(3) == "1") {
			game->itemTaken = true;
		} else {
			game->itemTaken = false;
		}


		getline(myfile, line);
		parts = StringSplit(line, ':'); // PREV_INS_X:PREV_INS_Y:PREV_TMPINS_X:PREV_TMPINS_Y:PREV_POS_X:PREV_POS_Y
	    game->previousInsert.xPosition = stoi(parts.at(0));
	    game->previousInsert.yPosition = stoi(parts.at(1));
	    game->previousInsertTmp.xPosition = stoi(parts.at(2));
	    game->previousInsertTmp.yPosition = stoi(parts.at(3));
	    game->previousPosition.xPosition = stoi(parts.at(4));
	    game->previousPosition.yPosition = stoi(parts.at(5));
	    myfile.close();

	} catch (...) {
        throw new InvalidFileException("Invalid file.", ErrorCode::_ERR_UNKNOWN);
    }

	return game;

}

Game *Game::NewGame(BoardSize boardSize, CardCount cardCount, PlayerCount playerCount) {

    Game *game = NULL;

    game = new Game(boardSize, cardCount, playerCount);
    game->InitializePlayerList();
    game->CreateStones();
    game->SplitStones();
    game->InitializeStones();
    game->RandomSetItems(cardCount);
    game->CreateCardPack();
	game->ShufflePack();
    game->SetPlayersOnBoard();

    HoldingTreasure::cards = cardCount;
    HoldingTreasure::players = playerCount;

    return game;

}


/* End of file game.cpp */
