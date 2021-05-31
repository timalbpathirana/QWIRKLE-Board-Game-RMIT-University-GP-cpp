#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "Tile.h"
#include "LinkedList.h"
#include "Player.h"
#include "Board.h"
#include "TilesBag.h"


// Game functions
void gameInit(Player* player1, Player* player2);

void startTheGame();

void saveGame(Player* player1, Player* player2, Board* board, std::string fileName, LinkedList* tilesBag, std::string currentPlayer );


void showCredits();

void loadGame(Player* player1, Player* player2, Board* board, std::string fileName, LinkedList* tilesBag, int* turn, bool* qwirkleRowCheck, bool* qwirkleColCheck);

void getUserInfo(Player* player1, Player* player2);

bool isInputValid(std::string input);

void playRound(Player* currentPlayer, Board* board, TilesBag* tilesBag, bool* qwirkleRowCheck, bool* qwirkleColCheck, Player* otherPlayer);

//Testing variables and methods
bool IsTestingModeOn = false;
void successfullGameLoadTesting();
void successfulGameInitTesting();  
void sucessfullGameSaveTesting();
void linkedListTesting();
void nodeTesting();
void playerTesting();
void tileTesting();
void tileBagTesting();
void boardTesting();


int main(void) {

    if(IsTestingModeOn == true){
    std::cout << "TESTING STARTED" << std::endl;
    std::cout << '\n';
    std::cout << "You are on Testing Mode" << '\n';
    std::cout << "Please turn IsTestingModeOn = False to start a new game!" << std::endl;
    std::cout << '\n';

    //successfullGameLoadTesting();         /*   Passing      */
    // successfulGameInitTesting();         /*   Passing      */
    // sucessfullGameSaveTesting();         /*     TODO       */
    // linkedListTesting();                 /*   Failing      */ // is the fix ok?
    // nodeTesting();                       /*   Passing      */
    // playerTesting();                     /*   Passing      */
    // tileTesting();
    // boardTesting();                      /*   Failing TODO */ // some initial testing added, is it ok?

    std::cout << '\n';
    std::cout << "TESTING FINISHED" << std::endl;
    std::cout << '\n';

    }
    else {
    // Game starts here
    startTheGame();

    }

    return EXIT_SUCCESS;
};



void startTheGame() {
    std::string userInputValue;

    std::cout << '\n';
    std::cout << "Welcome to Qwirkle!" << '\n';
    std::cout << "-------------------" << '\n';

    // Displaying the menu 
    std::cout << '\n';
    std::cout << "Menu" << '\n';
    std::cout << "----" << '\n';
    std::cout << '\n';



    TilesBag* tilesBag = new TilesBag();
    Board* board = new Board();
    Player* player1 = new Player(1);
    Player* player2 = new Player(2);
    std::string currentPlayer = "";
    std::string fileName = "";
    int turn = 0;
    bool qwirkleRowCheck = false;
    bool qwirkleColCheck = false;
    
    // Printing the Options 
    std::cout << "1. New Game" << '\n';
    std::cout << "2. Load Game" << '\n';
    std::cout << "3. Credits (Show student information)" << '\n';
    std::cout << "4. Quit" << '\n';
    std::cout << '\n';

    bool correctInput = false;
    while (!correctInput && !std::cin.eof()) {
        std::cout << '\n';
        std::cout << ">" ;
        std::cin >> userInputValue;
        if (userInputValue == "1" || userInputValue == "2" || userInputValue == "3" || userInputValue == "4") {
            correctInput = true;
        } else if (std::cin.eof()) { 
            std::cout << "Terminated." << std::endl;
        }
    }

    if (correctInput) {
        if (userInputValue == "1") { // menu choice 1
            getUserInfo(player1, player2);
            tilesBag->initBag();
            tilesBag->shuffleBag();

            player1->setPlayerHand(tilesBag->moveTileFromBagToPlayerHand(MAX_TILES_IN_HAND));
            player2->setPlayerHand(tilesBag->moveTileFromBagToPlayerHand(MAX_TILES_IN_HAND));

            std::cin.clear();
            std::cin.ignore();

            std::cout << "player 1 hand size: " << player1->getPlayerHand()->getSize() << std::endl;
            std::cout << "player 2 hand size: " << player2->getPlayerHand()->getSize() << std::endl;

            turn = 1;
            while ((player1->getPlayerHand()->getSize() > 0 && player2->getPlayerHand()->getSize() > 0) && !std::cin.eof()) {
                if (turn == 1) {
                    playRound(player1, board, tilesBag, &qwirkleRowCheck, &qwirkleColCheck, player2);
                    turn = 2;
                } else {
                    playRound(player2, board, tilesBag, &qwirkleRowCheck, &qwirkleColCheck, player1);
                    turn = 1;
                }
            }
        }
        else if(userInputValue == "2"){ // menu choice 2
            loadGame(player1, player2, board, fileName, tilesBag->getTiles(), &turn, &qwirkleRowCheck, &qwirkleColCheck);
            std::cin.clear();
            std::cin.ignore();
            // board->printPlayingBoard();
            // std::cout << "player 1 hand size: " << player1->getPlayerHand()->getSize() << std::endl;
            // std::cout << "player 2 hand size: " << player2->getPlayerHand()->getSize() << std::endl;
            
            // after game loaded - resume game
            while ((player1->getPlayerHand()->getSize() > 0 && player2->getPlayerHand()->getSize() > 0) && !std::cin.eof()) {
                if (turn == 1) {
                    playRound(player1, board, tilesBag, &qwirkleRowCheck, &qwirkleColCheck, player2);
                    turn = 2;
                } else {
                    playRound(player2, board, tilesBag, &qwirkleRowCheck, &qwirkleColCheck, player1);
                    turn = 1;
                }
            }
            
            // end game
            std::cout << "Game ended - results: " << std::endl;
            std::cout << "Board: " << std::endl;
            board->printPlayingBoard();
            std::cout << "Player 1: " << player1->getPlayerName() << std::endl;
            std::cout << "Score: " << player1->getPlayerPoints() << std::endl;
            std::cout << "Player 2: " << player2->getPlayerName() << std::endl;
            std::cout << "Score: " << player2->getPlayerPoints() << std::endl;
            if (player1->getPlayerPoints() > player2->getPlayerPoints()) {
                std::cout << "Player 1 Wins!" << std::endl; 
            } else if (player1->getPlayerPoints() < player2->getPlayerPoints()) {
                std::cout << "Player 2 Wins!" << std::endl; 
            } else {
                std::cout << "Draw game." << std::endl; 
            }
        }
        else if(userInputValue == "3"){ // menu choice 3
            showCredits();

        } else if(userInputValue == "4"){
            std::cout << "Good Bye !" << std::endl;
        } 
    }
}

// Game functions starts here

void getUserInfo(Player* player1, Player* player2){
    std::string playerOneName;
    std::string playerTwoName;


    std::cout << "Starting a New Game" << '\n';

    // Getting 1st Player name and validate 
    std::cout << '\n';
    std::cout << "Enter a single name for player 1 (uppercase characters only)" << '\n';
    do
    {
        std::cout << ">";
        std::cin >> playerOneName;
    } while (!isInputValid(playerOneName));

    // Getting 2nd Player name and validate 
    std::cout << '\n';
    std::cout << "Enter a name for player 2 (uppercase characters only)" << '\n';
    
    do
    {
        std::cout << ">";
        std::cin >> playerTwoName;
    } while (!isInputValid(playerTwoName));


    // Setting up playern names
   player1->setPlayerName(playerOneName);
   player2->setPlayerName(playerTwoName);

    std::cout << '\n';
    std::cout << "Let's Play!" << '\n';
    std::cout << '\n';


}


void playRound(Player* currentPlayer, Board* board, TilesBag* tilesBag, bool* qwirkleRowCheck, bool* qwirkleColCheck, Player* otherPlayer) {
    std::cout << std::endl;

    std::cout << currentPlayer->getPlayerName() << std::endl;
    std::cout << "It's your turn" << std::endl;
    std::cout << "your score: ";
    std::cout << currentPlayer->getPlayerPoints() << std::endl;
    std::cout << std::endl;

    board->printPlayingBoard();
    std::cout.clear();

    std::cout << "your hand is: " << std::endl;
    for (int i = 0; i < currentPlayer->getPlayerHand()->getSize(); i++) {
        std::cout << currentPlayer->getPlayerHand()->getIndex(i)->getTileCode() << ' ';
    }
    std::cout << std::endl;

    bool checkSuccess = false;      /* checkSuccess use To validate overall command */
    bool placeSuccess = true;       /* placeSuccess use To validate the place command */
    bool replaceSuccess = true;     /* replaceSuccess use To validate the replace command */
  
    while (!checkSuccess && !std::cin.eof()) {
        std::cout << "> ";
        std::string command = "";
        std::string commandString;
        std::getline(std::cin, commandString); // get the entire command
        // commandString = lineCheck;
        std::stringstream commandStream(commandString);

        bool checkCommand = false;
        commandStream >> command;
        if (command == "place" || command == "replace" || command == "save") { // checck the 1st command
            checkCommand = true;
        }
        
        if (checkCommand) {
            if (command == "place") {

                // place <tile> at <coordinate>
                bool checkTile = false;
                std::string tileString;
                commandStream >> tileString;
                    if (currentPlayer->getPlayerHand()->getData(tileString) != nullptr) { 
                        // check if tile exists in player's hand
                        checkTile = true;
                    }

                bool checkAt = false;
                std::string at;
                commandStream >> at;
            
    
            if (at == "at") { // check if the 3rd command is "at"
                checkAt = true;
            }
            else {
                checkSuccess = false;
                placeSuccess = false;
            }

            bool checkCoordinate = false;
            std::string coordinate;
            commandStream >> coordinate;
            char row = coordinate[0];
            std::string colSub = coordinate.substr(1);
            std::stringstream colStr(colSub);
            int col = 0;
            colStr >> col;
                // row-65 == char to int coversion - (int) someChar
            if ((row-65) >= 0 && (row-65) <= 25 && col >= 0 && col <= 25) { // check if the row and col are correct
                checkCoordinate = true;
            }
            else{
                std::cout << "Wrong Cordinated" << '\n';
            }

            if (checkTile && checkAt && checkCoordinate) { // all correct
                    // check if the tile was placed successfully > then add points
                bool placedSuccess = false;
                placedSuccess = board->placeTile(currentPlayer->getPlayerHand()->getData(tileString), row, col, qwirkleRowCheck, qwirkleColCheck);
                    if (placedSuccess) {
                        currentPlayer->setPlayerPoints(currentPlayer->getPlayerPoints() + 2);
                        currentPlayer->getPlayerHand()->deleteData(tileString); // delete the tile from player
                            if (*qwirkleRowCheck) { // check if qwirkle at row > then add bonus points
                            std::cout << "QWIRKLE!" << std::endl;
                            currentPlayer->setPlayerPoints(currentPlayer->getPlayerPoints() + 6);
                            }
                            if(*qwirkleColCheck) { // check if qwirkle at col > then add bonus points
                                std::cout << "QWIRKLE!" << std::endl;
                                currentPlayer->setPlayerPoints(currentPlayer->getPlayerPoints() + 6);
                            }
                        }
                *qwirkleRowCheck = false; // reset qwirkle check
                *qwirkleColCheck = false; // reset qwirkle check

                    if (tilesBag->getTiles()->getSize() > 0){
                        // add new tile after added
                        // currentPlayer->getPlayerHand()->addBack(tilesBag->getAndRemoveRandom());
                        currentPlayer->getPlayerHand()->addBack(tilesBag->getTiles()->getFront()); // copy tile at the front of the bag
                        tilesBag->getTiles()->deleteFront();
                    }

                    std::cout << std::endl;
                    if (placedSuccess) {
                        checkSuccess = true; // if success this big loop terminates
                        std::cout << "Your hand at end of turn is: " << std::endl;
                        for (int i = 0; i < currentPlayer->getPlayerHand()->getSize(); i++) {
                            std::cout << currentPlayer->getPlayerHand()->getIndex(i)->getTileCode() << ' ';
                        }
                    }
                    std::cout << std::endl;
                }
            } 
            else if (command == "replace") { // player wants to replace a tile
                // replace <tile>
                std::string tileString;
                commandStream >> tileString;

                bool checkTile = false;
                if (currentPlayer->getPlayerHand()->getData(tileString) != nullptr) { // check if tile exists in player's hand
                    checkTile = true;
                }
                else{
                    checkSuccess = false;
                }

                if (checkTile) { // replace the tile
                    Tile* playerTile = new Tile(*(currentPlayer->getPlayerHand()->getData(tileString))); // the player wants to replace

                    if(tilesBag->getTiles()->getSize() > 0){
                        Tile* bagTile = new Tile(*tilesBag->getTiles()->getFront()); // the player will be added this from bag
                        currentPlayer->getPlayerHand()->deleteData(tileString);
                        currentPlayer->getPlayerHand()->addBack(bagTile);
                        tilesBag->getTiles()->addBack(playerTile);
                        std::cout << "your hand replaced is: " << std::endl;
                            for (int i = 0; i < currentPlayer->getPlayerHand()->getSize(); i++) {
                                std::cout << currentPlayer->getPlayerHand()->getIndex(i)->getTileCode() << ' ';
                            }
                        checkSuccess = true;
                        std::cout << std::endl;
                    }
                    else {
                        checkSuccess = false;
                        replaceSuccess = false;
                    }
                    
                }
            } else if (command == "save") {
                std::string saveName = "";
                commandStream >> saveName;

                saveGame(currentPlayer, otherPlayer, board, saveName, tilesBag->getTiles(), currentPlayer->getPlayerName());
            }
            else {
            checkSuccess = false;
            placeSuccess = false;
        }
        }
        if (!checkSuccess) {
            if (command != "save" && !std::cin.eof() && placeSuccess == false) {
                
                    std::cout << "Invalid command." << std::endl;
                    std::cout << std::endl;
                    std::cout << "Please use the Syntax form of 'place <Tile> at <Cordinate>'" << std::endl;
                    std::cout << std::endl;
            }
            else if(command != "save" && !std::cin.eof() && replaceSuccess == false){
                    std::cout << "Sorry, there are no more tiles left to replace." << std::endl;
                    std::cout << std::endl;
            } 
            
            if (std::cin.eof()) {
                std::cout << "Terminated" << std::endl;
            }
        } else {
            std::cout << "---END TURN---" << std::endl;
        }
    }
}

void loadGame(Player* player1, Player* player2, Board* board, std::string fileName, LinkedList* tilesBag, int* turn, bool* qwirkleRowCheck, bool* qwirkleColCheck){

    
    std::string userInputFileName;
    if(IsTestingModeOn == true){
        userInputFileName = "TestFiles/GameTesting/LoadingTesting/loadFile1.input";
    
    } 
    else {
    std::cout << "Enter the filename from which load a game " << '\n';
    std::cout << ">";
    std::cin >> userInputFileName;
    // userInputFileName = "testSave";
    
    }
    /*
    <player 1 name>
    <player 1 score>
    <player 1 hand>
    <player 2 name>
    <player 2 score>
    <player 2 hand>
    <Current board shape>
    <Board State>
    <tile bag contents>
    <current player name>
    */

    std::string line;
    std::ifstream myfile;
    myfile.open(userInputFileName);

    if(!myfile.is_open()) {
      perror("Error open");
      std::cout  << '\n';
      std::cout << "Game Load Unsuccessful! Please check your file again.." << '\n';
      std::cout  << '\n';
      exit(EXIT_FAILURE);
    }
    else {
    int index = 0;
    while(getline(myfile, line)) {
        if (index == 0 && isInputValid(line)){
            player1->setPlayerName(line);

            if(IsTestingModeOn){
                std::cout << "Player 1 name loaded successfully" << ": " << player1->getPlayerName() << '\n';
            }
            
            
        } 
        else if (index == 1) {
            int p1point;
            std::stringstream stream(line);
            stream >> p1point;
            player1->setPlayerPoints(p1point);

            if(IsTestingModeOn){
                std::cout << "Player 1 score loaded successfully" << ": " << player1->getPlayerPoints()<< std::endl;
            }
            
            
        } 
        else if (index == 2) {
            
            std::stringstream stream(line);
            char readIn = '0';
            char colourChar = '0';
            int numInt = 0;
            while (stream.get(readIn)) {
                if (readIn == 'R' || readIn == 'O' || readIn == 'Y' || readIn == 'G' || readIn == 'B' || readIn == 'P') {
                    colourChar = readIn;
                } else if (readIn == '1' || readIn == '2' || readIn == '3' || readIn == '4' || readIn == '5' || readIn == '6') {
                    numInt = readIn-'0';
                } else {
                    colourChar = '0';
                    numInt = 0;
                }

                if (colourChar != '0' && numInt != 0) {
                    player1->getPlayerHand()->addBack(new Tile(colourChar, numInt));
                }
            }

            if(IsTestingModeOn){
                std::cout << "Player 1 hand loaded successfully" << ": " << player1->getPlayerHand()->getSize() << std::endl;
            }
        } 
        else if (index == 3 && isInputValid(line)) {
            player2->setPlayerName(line);
            if(IsTestingModeOn){
                std::cout << "Player 2 name loaded successfully" << ": " << player2->getPlayerName() << std::endl;
            }
        } 
        else if (index == 4) {
            int p2point;
            std::stringstream stream(line);
            stream >> p2point;
            player2->setPlayerPoints(p2point);
            if(IsTestingModeOn){
                std::cout << "Player 2 score loaded successfully" <<": " << player2->getPlayerPoints() << std::endl;
            }
        } 
        else if (index == 5) {
            
            std::stringstream stream(line);
            char readIn = '0';
            char colourChar = '0';
            int numInt = 0;
            while (stream.get(readIn)) {
                if (readIn == 'R' || readIn == 'O' || readIn == 'Y' || readIn == 'G' || readIn == 'B' || readIn == 'P') {
                    colourChar = readIn;
                } else if (readIn == '1' || readIn == '2' || readIn == '3' || readIn == '4' || readIn == '5' || readIn == '6') {
                    numInt = readIn-'0';
                } else {
                    colourChar = '0';
                    numInt = 0;
                }

                if (colourChar != '0' && numInt != 0) {
                    player2->getPlayerHand()->addBack(new Tile(colourChar, numInt));
                }
            }

            if(IsTestingModeOn) {
                std::cout << "Player 2 hand loaded successfully" << ": " << player2->getPlayerHand()->getSize() << std::endl;
            }
        } 
        else if (index == 6) {
            if(IsTestingModeOn){
                std::cout << "Loading current Board...." << std::endl;
            }
            
        } 
        else if (index == 7) {
            
            // board state
            std::stringstream stream(line);
            std::string object;
            while(getline(stream, object, ' '))
            {
                // The line passed though here will need to be an individual tile 
                
                board->placeTileString(object, qwirkleRowCheck, qwirkleColCheck);
            }
            
            
            if(IsTestingModeOn){
                std::cout << "Loading Board status" << std::endl;
                board->printPlayingBoard();
            }
        } 
        else if (index == 8) {
            // set tiles bag
            std::stringstream stream4(line);
            char readIn = '0';
            char colourChar = '0';
            int numInt = 0;
            while (stream4.get(readIn)) {
                if (readIn == 'R' || readIn == 'O' || readIn == 'Y' || readIn == 'G' || readIn == 'B' || readIn == 'P') {
                    colourChar = readIn;
                } else if (readIn == '1' || readIn == '2' || readIn == '3' || readIn == '4' || readIn == '5' || readIn == '6') {
                    numInt = readIn-'0';
                } else {
                    colourChar = '0';
                    numInt = 0;
                }

                if (colourChar != '0' && numInt != 0) {
                    tilesBag->addBack(new Tile(colourChar, numInt));
                }
            }

            if(IsTestingModeOn){
                std::cout << "Loading TileBag content...." << std::endl;
            }
            
        } 
        else if (index == 9) {
            // Made currentPlayer variable for testing purposes
            std::string currentPlayer ="";
            if (line == player1->getPlayerName().substr(0, line .size())) {
                currentPlayer = player1->getPlayerName();
                *turn = 1; 
            } else if (line  == player2->getPlayerName().substr(0, line.size())) {
                *turn = 2;
                currentPlayer = player2->getPlayerName();
            } else {
                *turn = 1;
            }

            if(IsTestingModeOn){
                std::cout << "Loading current player..." << std::endl;
                std::cout << "Current player: " << currentPlayer << std::endl;
            }
        }
        else {
            std::cout << "Else triggered" << std::endl;
        } 
        index++;
    }
    }

    std::cout << userInputFileName << " has been loaded Successfully ! " << std::endl;
    // Adding some line space
    std::cout << std::string( 10, '\n' );

};

void showCredits(){
    std::string line;
    std::ifstream myfile;
    myfile.open("studentCredits.txt");

   if(!myfile.is_open()) {
      perror("Error open");
      exit(EXIT_FAILURE);
   }
    while(getline(myfile, line)) {
    std::cout << line << std::endl;
    }
    startTheGame();

};

void saveGame(Player* player1, Player* player2, Board* board, std::string fileName, LinkedList* tilesBag, std::string currentPlayer ){

    std::ofstream file;
    file.open(fileName, std::ios_base::app);

    file << player1->getPlayerName() << std::endl;
    file << player1->getPlayerPoints() << std::endl;
    LinkedList* player1Hand = player1->getPlayerHand();
    for (int i = 0; i < player1Hand->getSize() ; i++){

        // should be colour, number
        file << player1Hand->getIndex(i)->getTileCode();
        file << ",";

    }
    file << std::endl;


    file << player2->getPlayerName() << std::endl;
    file << player2->getPlayerPoints() << std::endl;
    LinkedList* player2Hand = player2->getPlayerHand();
    for (int i = 0; i < player2Hand->getSize() ; i++){

        file << player2Hand->getIndex(i)->getTileCode();
        file << ",";

    }
    file << std::endl;

    // board shape
    file << board->getHeight();
    file << board->getWidth() << std::endl;

    // board state
    std::vector<std::string> boardState = board->getplacedTiles();
    for (unsigned int i = 0; i < boardState.size() ; i++){
        file << boardState[i];
        
        if (i == boardState.size()-1){
            // do not print comma
        } else {
            file << ", ";
        }
    } 
    file << std::endl;

    // tile bag content
    for (int i = 0; i < tilesBag->getSize() ; i++){

        file << tilesBag->getIndex(i)->getTileCode();
        file << ", ";

    }
    file << std::endl;


    // current player name
    file << currentPlayer;

    file.close();
    std::cout << "Game has been saved Successfully ! " << std::endl;
};

void gameInit(Player* player1, Player* player2){

    // Making a new tile bag object and initialising the bag    
    TilesBag* tilesBag = new TilesBag();
    tilesBag->initBag();
    
    // Print only on Test Mode
    if(IsTestingModeOn) {
        std::cout << std::endl;
        std::cout << "-------------------Initial Bag--------------------" << std::endl;
        tilesBag->printBag(); 

        std::cout << std::endl;
        std::cout << "-------------------Shuffled Bag-------------------" << std::endl;
        tilesBag->setTiles(tilesBag->getTiles());
        tilesBag->printBag();

    }


    // Creating new player hand linkedLists
   LinkedList* firstPlayerHand = new LinkedList();
   LinkedList* secondPlayerHand = new LinkedList();

   //Assigning 6 tiles randomly from the bag to each player
   firstPlayerHand = tilesBag->moveTileFromBagToPlayerHand(MAX_TILES_IN_HAND);
   secondPlayerHand = tilesBag->moveTileFromBagToPlayerHand(MAX_TILES_IN_HAND);
   

    player1->setPlayerHand(firstPlayerHand);
    player2->setPlayerHand(secondPlayerHand);
   
}


bool isInputValid(std::string input) {
    
    bool toReturn = true;

    /* this for loop is checking if the input has any special characters,numbers or lowercase letters.
    If there are any non characters, the index will update with the position that triggers toReturn to false. 
    To begin, Making index to -1 as it will never go below 0 inside the loop
    */
    int index = -1;
    // for (unsigned int i = 0; i < input.length(); i++) {
    //     std::cout << "index: " << i << ": " << (int)input[i] << std::endl;
    // }
    // for (unsigned int i = 0; i < input.length(); i++)
    // {
        index = input.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ\r",0);
        if (index != -1){
            toReturn = false;
            
        }
    // }
    // Printing invalid input to the terminal 
    if (index != -1){
            std::cout << "Invalid Input" << "\n";
            
        }
    return toReturn;
    
}

void boardTesting(){
    Board* testBoard = new Board();

    // Making new tiles
    Tile* testTile = new Tile('R', 1);
    Tile* testTile2 = new Tile('R', 2);
    Tile* testTile3 = new Tile('R', 5);
    Tile* testTile4 = new Tile('R', 2); // same tile as testTile2
    Tile* testTile5 = new Tile('O', 1);
    Tile* testTile6 = new Tile('G', 1);
    Tile* testTile7 = new Tile('O', 5);
    Tile* testTile8 = new Tile('G', 5);
    Tile* testTile9 = new Tile('B', 5);
    Tile* testTile10 = new Tile('G', 2);
    Tile* testTile11 = new Tile('O', 4);
    Tile* testTile12 = new Tile('O', 2);
    Tile* testTile13 = new Tile('P', 1);
    Tile* testTile14 = new Tile('Y', 1);
    Tile* testTile15 = new Tile('Y', 2);
    Tile* testTile16 = new Tile('Y', 5);
    Tile* testTile17 = new Tile('P', 5);
    Tile* testTile18 = new Tile('O', 5);

    bool* qwirkleRow = new bool(false);
    bool* qwirkleCol = new bool(false);

    testBoard->placeTile(testTile, 'Z', 25, qwirkleRow, qwirkleCol);
    testBoard->placeTile(testTile2, 'Z', 24, qwirkleRow, qwirkleCol);
    testBoard->placeTile(testTile3, 'Z', 23, qwirkleRow, qwirkleCol);
    testBoard->placeTile(testTile4, 'Z', 22, qwirkleRow, qwirkleCol); // should not be placed as row Z already has R2
    testBoard->placeTile(testTile5, 'Y', 25, qwirkleRow, qwirkleCol);
    testBoard->placeTile(testTile6, 'X', 25, qwirkleRow, qwirkleCol);
    testBoard->placeTile(testTile7, 'Y', 23, qwirkleRow, qwirkleCol);
    testBoard->placeTile(testTile8, 'X', 23, qwirkleRow, qwirkleCol);
    testBoard->placeTile(testTile9, 'X', 22, qwirkleRow, qwirkleCol);
    testBoard->placeTile(testTile10, 'X', 24, qwirkleRow, qwirkleCol); // should not be placed as left side has a rule: shape 5 only
    testBoard->placeTile(testTile11, 'Y', 24, qwirkleRow, qwirkleCol); // should not be placed, fit row, but NOT fit col
    testBoard->placeTile(testTile12, 'Y', 24, qwirkleRow, qwirkleCol); // this one should be placed because fits row and col
    testBoard->placeTile(testTile13, 'W', 25, qwirkleRow, qwirkleCol);
    testBoard->placeTile(testTile14, 'V', 25, qwirkleRow, qwirkleCol);
    testBoard->placeTile(testTile15, 'V', 24, qwirkleRow, qwirkleCol);
    testBoard->placeTile(testTile16, 'V', 23, qwirkleRow, qwirkleCol);
    testBoard->placeTile(testTile17, 'W', 23, qwirkleRow, qwirkleCol);
    testBoard->placeTile(testTile18, 'X', 22, qwirkleRow, qwirkleCol); // should not be placed because B5 is already there
 
    std::cout << "Print board: " << std::endl;
    testBoard->printPlayingBoard();

    std::cout << "Board height: " << testBoard->getHeight() << std::endl;
    std::cout << "Board width: " << testBoard->getWidth() << std::endl;
    for (unsigned int i = 0; i < testBoard->getplacedTiles().size(); i++) {
        std::cout << testBoard->getplacedTiles()[i] << std::endl;
    }
}

void successfulGameInitTesting(){
    /*
    Test Case:  User Validation 

    Terminal Code: ./qwirkle <TestFiles/SuccessfulGameInit/UserValidation/userValidate.input   

    Test Description: In this test case, we are testing std::cin and validate user name

    Inputs vs Outputs:
        JOHn : Invalid Input
        JOHN
        MIK8 : Invalid Input
        MIKE
    */

   // Making test objects
    TilesBag* testTilesBag = new TilesBag();
    Player* firstTestPlayer = new Player(1);
    Player* secondTestPlayer = new Player(2);

    // triggering the method responsible for getting user names
    getUserInfo(firstTestPlayer, secondTestPlayer);
    testTilesBag->initBag();
    testTilesBag->shuffleBag();

    std::cout << "Player One: " << firstTestPlayer->getPlayerName() << '\n';
    std::cout << "Player Two: " << secondTestPlayer->getPlayerName() << '\n';
    std::cout << "Tile Bag Size " << testTilesBag->getTiles()->getSize() << '\n';

    // Freeing up the heap memeoy
   delete firstTestPlayer;
   delete secondTestPlayer;

}

void successfullGameLoadTesting() {
    /*
    Test Case: Successful Game Load from a file

    Terminal Code: ./qwirkle <TestFiles/GameTesting/LoadingTesting/loadFile1.input   

    Test Description: In this test case, we are testing different input files with different data sets
    */

   // Making test objects
    Player* testP1 = new Player(1);
    Player* testP2 = new Player(2);
    Board* testBoard = new Board();
    std::string userInputFileName = "";
    TilesBag* testBag = new TilesBag();
    int turn = 1;
    bool qwirkleRowCheck = false;
    bool qwirkleColCheck = false;

    loadGame(testP1, testP2,testBoard,userInputFileName,testBag->getTiles(),&turn, &qwirkleRowCheck,&qwirkleColCheck);

    delete testP1;
    delete testP2;
    delete testBoard;
    delete testBag;
    
}

void sucessfullGameSaveTesting() {
    //TODO
    /*
    Test Case: Successful Game Save to a file

    Terminal Code:   

    Test Description: In this test case, we are saving a snapshot of the game to a file.
    */
    Player* testP1 = new Player(1, "PONE");
    Player* testP2 = new Player(2, "PTWO");

    Board* testBoard = new Board();
    std::string userInputFileName = "";
    std::string currentPlayer = "PTWO";
    TilesBag* testBag = new TilesBag();

    saveGame(testP1, testP2, testBoard, userInputFileName, testBag->getTiles(),currentPlayer);


}

void linkedListTesting(){

    // creating a new liinkedlist
    LinkedList* testList = new LinkedList();

    /**
        * Adding tiles to the linkedlist
        * Tile constructor
        * input: 
        * colour code as char (R, O, Y, G, B, P)
        * shape code as int (1, 2, 3, 4, 5, 6)
        */
    /* 
        first test set: 
        inputs: R1
            Y3
            G4
            B7
            P2
            Y2

        Outputs:
            5



    */
    for (int i = 0; i < 5; i++)

    {
        char colour = 'R';
        int shape = 0;
        std::cin >> colour >> shape;

        Tile* testTile1 = new Tile(colour, shape);

        testList->addFront(testTile1); // this is adding to the front

        
        // delete testTile1; // deleting here means the linked list lose access to the tile object
    }
    // Getting final size
    std::cout << "size initial: " << testList->getSize() << '\n';
    // after the loop above the tiles should be ordered like so:
    /**
     * Y2
     * P2
     * B7
     * G4
     * Y3
     */

    // making 2 new tiles to test tile removal from the back
    Tile* deleteTileTest1 = new Tile('R', 2);
    Tile* deleteTileTest2 = new Tile('O', 4);

    //Adding newly created deleteTestTiles to the tileList
    // Total amount of tiles should be 7

    testList->addBack(deleteTileTest1);
    testList->addBack(deleteTileTest2);
    // after the adding the 2 tiles above the tiles should be ordered like so:
    /**
     * Y2
     * P2
     * B7
     * G4
     * Y3
     * R2
     * O4
     */

    std::cout << "size after added 2: " << testList->getSize() << '\n';

    // Tile removal process
    /*
    Output cannot be like this because used addFront in the loop above: 
        6
        Yellow:3
        Green:4
        Blue:7
        Purple:2
        Yellow:2
        Red:2
    */

   /*
    Output should be: 
        size after delete 1: 6
        Yellow:2
        Purple:2
        Blue:7
        Green:4
        Yellow:3
        Red:2
    */

    testList->deleteBack();
    std::cout << "size after delete 1: " << testList->getSize() << '\n';


    for (int i = 0; i < testList->getSize(); i++)
    {
        std::cout << testList->getIndex(i)->getColourString()<<':'<< testList->getIndex(i)->getShapeCode() << '\n';
    }
}

void nodeTesting(){
     /*
    Test Case: Testing functionality of Node file
    Test Description: In this test case, we are testing all the functions inside Node class using Red/Circle tile.

    Output: R Circle R1
    */
    Tile* testTileOne = new Tile('R',1);
    Node* nxt = nullptr;
    Node* prev = nullptr;

    Node* testNodeOne = new Node(testTileOne,nxt, prev);
    

    std::cout << testNodeOne->getData()->getColourCode() << '\n';
    std::cout << testNodeOne->getData()->getShapeString() << '\n';
    std::cout << testNodeOne->getData()->getTileCode() << '\n';

    delete testTileOne;
}

void playerTesting(){
    /*
    Test Case: Testing functionality of Player file
    Test Description: In this test case, we are testing all the functions inside Player class.

    Output: JOHN 4 JAKE 7 10
    */
    Player* tPO = new Player(4, "JOHN");
    Player* tPT = new Player(7, "JAKE");

    std::cout << tPO->getPlayerName() << '\n';
    std::cout << tPO->getPlayerNum() << '\n';
    std::cout << tPT->getPlayerName() << '\n';
    std::cout << tPT->getPlayerNum() << '\n';

    // Setting up point for first player
    tPO->setPlayerPoints(10);
    std::cout << tPO->getPlayerPoints() << '\n';



}
