#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>

#include "Tile.h"
#include "LinkedList.h"
#include "Player.h"
#include "Board.h"
#include "TilesBag.h"


// Game functions

void startTheGame();

// Function overloading
void saveGame(Player* player1, Player* player2, Board* board, std::string fileName, LinkedList* tilesBag, std::string currentPlayer );
void saveGame(Player* player1, Player* player2, Player* player3, Board* board, std::string fileName, LinkedList* tilesBag, std::string currentPlayer );

void loadGame(Player* player1, Player* player2, Board* board, std::string fileName, LinkedList* tilesBag, int* turn, bool* qwirkleRowCheck, bool* qwirkleColCheck);
void loadGame(Player* player1, Player* player2, Player* player3, Board* board, std::string fileName, LinkedList* tilesBag, int* turn, bool* qwirkleRowCheck, bool* qwirkleColCheck);

void playRound(Player* currentPlayer, Board* board, TilesBag* tilesBag, bool* qwirkleRowCheck, bool* qwirkleColCheck, Player* secondPlayer, Player* thirdPlayer);

void showCredits();
void getUserInfo(Player* player1, Player* player2, Player* player3);
bool isInputValid(std::string input);
std::string EnStatusCheck(bool bStatus);
void goBack();
void lineBreak();
void print(std::string s);



bool helpMode = false;
bool betterInputValidation = false;
bool threePlayerMode = false;
bool placeMoreTiles = false;
int chosenOption = 0;


int main(void) {
    startTheGame();

    return EXIT_SUCCESS;
};


void startTheGame() {
    std::string userInputValue;


    lineBreak();
    print("Welcome to Qwirkle!");
    print("-------------------");

    // Displaying the menu 
    lineBreak();
    print("Menu");
    print("----");
    lineBreak();

    TilesBag* tilesBag = new TilesBag();
    Board* board = new Board();
    Player* player1 = new Player(1);
    Player* player2 = new Player(2);
    Player* player3 = new Player(3);


    std::string currentPlayer = "";
    std::string fileName = "";
    int turn = 0;
    bool qwirkleRowCheck = false;
    bool qwirkleColCheck = false;
    // Printing the Options 
    print("1. New Game");
    print("2. Load Game");
    print("3. Credits (Show student information)");
    print("4. Settings");
    lineBreak();
    print("5. Quit");
    lineBreak();

    bool correctInput = false;

    while (!correctInput && !std::cin.eof()) {
        lineBreak();
        std::cout << ">" ;
        std::cin >> userInputValue;
        if (userInputValue == "1" || userInputValue == "2" || userInputValue == "3" || userInputValue == "4" || userInputValue == "5"  || userInputValue == "help") {
            correctInput = true;
        } else if (std::cin.eof()) { 
            print("Good Bye");
        }
    }

    if (correctInput) {
        if (userInputValue == "1") { // menu choice 1
            
            getUserInfo(player1, player2, player3);
            if(threePlayerMode){
                tilesBag->initBagForM3();
            }
            else{
                tilesBag->initBag();
            }

            tilesBag->shuffleBag();

            player1->setPlayerHand(tilesBag->moveTileFromBagToPlayerHand(MAX_TILES_IN_HAND));
            player2->setPlayerHand(tilesBag->moveTileFromBagToPlayerHand(MAX_TILES_IN_HAND));
            // Making a player 3 anyway to fulfil the playRound function parameters
            player3->setPlayerHand(tilesBag->moveTileFromBagToPlayerHand(MAX_TILES_IN_HAND));


            std::cin.clear();
            std::cin.ignore();

            std::cout << "player 1 hand size: " << player1->getPlayerHand()->getSize() << std::endl;
            std::cout << "player 2 hand size: " << player2->getPlayerHand()->getSize() << std::endl;

            if(threePlayerMode){
                std::cout << "player 3 hand size: " << player3->getPlayerHand()->getSize() << std::endl;
            }

            
                turn = 1;
                while ((player1->getPlayerHand()->getSize() > 0 && player2->getPlayerHand()->getSize() > 0 && player3->getPlayerHand()->getSize() > 0) && !std::cin.eof() ) {   

                    if(!threePlayerMode){
                        if (turn == 1) {
                            playRound(player1, board, tilesBag, &qwirkleRowCheck, &qwirkleColCheck, player2, player3);
                            turn = 2;
                        } else {
                            playRound(player2, board, tilesBag, &qwirkleRowCheck, &qwirkleColCheck, player1, player3);
                            turn = 1;
                        }
                    }
                    //If Only threePlayerMode is no, it will loop on 3 round loop.
                    else {
                        if (turn == 1) {
                            playRound(player1, board, tilesBag, &qwirkleRowCheck, &qwirkleColCheck, player2, player3);
                            turn = 2;
                        } else if (turn == 2){
                            playRound(player2, board, tilesBag, &qwirkleRowCheck, &qwirkleColCheck, player1, player3);
                            turn = 3;
                        }
                        else if(turn == 3){
                            playRound(player3, board, tilesBag, &qwirkleRowCheck, &qwirkleColCheck, player1, player2);
                            turn = 1;
                        }
                    }

                }
            
        }
        else if(userInputValue == "2"){ // menu choice 2

            if(threePlayerMode){
                loadGame(player1,player2,player3, board, fileName, tilesBag->getTiles(), &turn, &qwirkleRowCheck, &qwirkleColCheck); 

                std::cin.clear();
                std::cin.ignore();

                while ((player1->getPlayerHand()->getSize() > 0 && player2->getPlayerHand()->getSize() > 0 && player3->getPlayerHand()->getSize() > 0) && !std::cin.eof()) {
                    if (turn == 1) {
                        playRound(player1, board, tilesBag, &qwirkleRowCheck, &qwirkleColCheck, player2, player3);
                        turn = 2;
                    }else if (turn == 2) {
                        playRound(player2, board, tilesBag, &qwirkleRowCheck, &qwirkleColCheck, player1, player3);
                        turn = 3;
                    }
                    else {
                        playRound(player3, board, tilesBag, &qwirkleRowCheck, &qwirkleColCheck, player1, player2);
                        turn = 1;
                    }
                }
            }
            else {
                loadGame(player1, player2, board, fileName, tilesBag->getTiles(), &turn, &qwirkleRowCheck, &qwirkleColCheck);

                std::cin.clear();
                std::cin.ignore();
                // Making the player3 object to pass the playRound function. 
                Player* player3 = new Player(3);

                while ((player1->getPlayerHand()->getSize() > 0 && player2->getPlayerHand()->getSize() > 0) && !std::cin.eof()) {
                    if (turn == 1) {
                        playRound(player1, board, tilesBag, &qwirkleRowCheck, &qwirkleColCheck, player2, player3);
                        turn = 2;
                    }else {
                    playRound(player2, board, tilesBag, &qwirkleRowCheck, &qwirkleColCheck, player1, player3);
                    turn = 1;
                    }
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


            if(threePlayerMode){
                std::cout << "Player 3: " << player3->getPlayerName() << std::endl;
                std::cout << "Score: " << player3->getPlayerPoints() << std::endl;
            }
            
            if (player1->getPlayerPoints() > player2->getPlayerPoints()) {

                if(threePlayerMode == true && player1->getPlayerPoints() > player3->getPlayerPoints()){
                    std::cout << "Player 1 Wins!" << std::endl; 
                }
                else if (threePlayerMode == true && player2->getPlayerPoints() > player3->getPlayerPoints()){
                    std::cout << "Player 2 Wins!" << std::endl;
                }
                else if (threePlayerMode == true && player2->getPlayerPoints() < player3->getPlayerPoints()) {
                    std::cout << "Player 3 Wins!" << std::endl;
                }
                else {
                    std::cout << "Player 1 Wins!" << std::endl;
                }

            } else if (player2->getPlayerPoints() > player1->getPlayerPoints()) {
                if(threePlayerMode == true && player2->getPlayerPoints() > player3->getPlayerPoints()){
                    std::cout << "Player 2 Wins!" << std::endl; 
                }
                else if (threePlayerMode == true && player3->getPlayerPoints() > player1->getPlayerPoints()){
                    std::cout << "Player 3 Wins!" << std::endl;
                }
                else if (threePlayerMode == true && player3->getPlayerPoints() < player1->getPlayerPoints()) {
                    std::cout << "Player 1 Wins!" << std::endl;
                }
                else {
                    std::cout << "Player 2 Wins!" << std::endl;
                }
            } else {
                std::cout << "Draw game." << std::endl; 
            }
            EXIT_SUCCESS;
        }

        else if(userInputValue == "3"){ // menu choice 3
            showCredits();

        } 
        else if (userInputValue == "4"){

            lineBreak();
            print("Menu >> Enhancements Settings");
            print("-----------------------------");
            lineBreak();
            print("INSTRUCTIONS");
            print("You can turn ON/OFF any option");
            lineBreak();
            print("Use command pattern as -> turn <Option number> <ON/OFF>");
            lineBreak();
            print("Eg: turn 1 OFF");
            lineBreak();
            lineBreak();

    
            std::cout << "1. Help Mode                  " << "Status:" << EnStatusCheck(helpMode) << '\n';
            std::cout << "2. Three-Player Mode          " << "Status:" << EnStatusCheck(threePlayerMode) << '\n';
            std::cout << "3. Placing 2 Tiles Mode       " << "Status:" << EnStatusCheck(placeMoreTiles) << '\n';
            std::cout << "4. Trigger All Options"<< '\n';  
            lineBreak();      

            

            while (!std::cin.eof()) {
                std::cout << ">";
                std::string command = "";
                std::string commandString;
                std::getline(std::cin, commandString); // get the entire command
                // commandString = lineCheck;
                std::stringstream commandStream(commandString);

                bool checkCommand = false;

                commandStream >> command;
                    if (command == "turn") { // checck the 1st command
                    checkCommand = true;
                    }
                    else if(command == "back"){
                        startTheGame();
                    }
            
                    if(checkCommand){
                       
                         std::string inputString;
                        commandStream >> inputString;
                        if (inputString == "1") { 
                            chosenOption = 1;
                        }
                        else if(inputString == "2"){
                            chosenOption = 2;
                        }
                        else if(inputString == "3"){
                            chosenOption = 3;
                        }
                        else if(inputString == "4"){
                            chosenOption = 4;
                        }

                        std::string onOffStatus;
                        commandStream >> onOffStatus;
            
                        // All the enhancement list
                        if (onOffStatus == "ON") { // check if the 3rd command is "at"
                            if(chosenOption == 1){
                                lineBreak();
                                print("Help is now ON!");
                                helpMode = true;
                                goBack();
                            }
                            else if (chosenOption == 2){
                                lineBreak();
                                print("Three-Player mode is now ON!");
                                threePlayerMode = true;
                                goBack();
                            }
                            // I added an option for the user to turn on help mode when user turning on the placing 2 tiles mode on for better user experience. 
                            else if (chosenOption == 3){
                                std::string s;
                                lineBreak();
                                print("Do you want to turn on Help Mode with this (YES/NO)?");
                                std::cin >> s;
                                if(s == "YES"){
                                    helpMode = true;
                                    print("Help is now ON!");
                                }
                                else if(s == "NO"){

                                }
                                else{
                                   print("INVALID ENTRY."); 
                                }
                                lineBreak();
                                print("Placing 2 Tiles Mode now ON!");
                                placeMoreTiles = true;
                                goBack();
                            }
                            else if(chosenOption == 4){
                                lineBreak();
                                print("All enhancements are now ON!");
                                helpMode = true;
                                threePlayerMode = true;
                                placeMoreTiles =true;
                                goBack();
                            }
                            
                        }
                        else if(onOffStatus == "OFF") {
                            if(chosenOption == 1){
                                lineBreak();
                                print("Help is now OFF!");
                                helpMode = false;
                                goBack();
                            
                            }
                            else if(chosenOption == 2){
                                lineBreak();
                                print("Three-Player mode is now OFF!");
                                threePlayerMode = false;
                                goBack();
                            }
                            else if(chosenOption == 3){
                                lineBreak();
                                print("Placing 2 Tiles Mode is now OFF!");
                                placeMoreTiles =false;
                                goBack();
                            }
                            else if(chosenOption == 4){
                                lineBreak();
                                print("All enhancements are now OFF!");
                                helpMode = false;
                                threePlayerMode = false;
                                placeMoreTiles =false;
                                goBack();
                            }
                        }

                    }
                    
            }
        }
        else if(userInputValue == "5"){
            std::cout << "Good Bye !" << std::endl;
        }

        else if(userInputValue == "help"){
            std::cout << "You are on the main menu" << std::endl;
            std::cout << "Please select any option on the list to navigate through the game" << std::endl;
            startTheGame();
        }
    }
    delete tilesBag;
    delete board;
    delete player1;
    delete player2;
    delete player3;
        
}


// M3 print and go back functions

void goBack(){
    lineBreak();
    std::cout << "You can go back to the main menu by typing 'back'" << '\n';

}

void lineBreak(){
    std::cout <<'\n';
}

void print(std::string s){
    std::cout <<s<<'\n';
}

// Timal - M3 function
std::string EnStatusCheck(bool bStatus){
    std::string returns ="OFF";
    if(bStatus == true){
        returns = "ON";
    }
    else if (bStatus == false){
        returns = "OFF";
    }
    return returns;
}

// Game functions starts here

void getUserInfo(Player* player1, Player* player2, Player* player3){
    std::string playerOneName;
    std::string playerTwoName;
    std::string playerThreeName;


    std::cout << "Starting a New Game" << '\n';

    // Getting 1st Player name and validate 
    lineBreak();
    std::cout << "Enter a single name for player 1 (uppercase characters only)" << '\n';
    do
    {
        std::cout << ">";
        std::cin >> playerOneName;
    } while (!isInputValid(playerOneName));

    // Getting 2nd Player name and validate 
    lineBreak();
    std::cout << "Enter a name for player 2 (uppercase characters only)" << '\n';
    
    do
    {
        std::cout << ">";
        std::cin >> playerTwoName;
    } while (!isInputValid(playerTwoName));

    if(threePlayerMode){
        lineBreak();
        std::cout << "Enter a single name for player 3 (uppercase characters only)" << '\n';
        do
        {
            std::cout << ">";
            std::cin >> playerThreeName;
        } while (!isInputValid(playerThreeName));
    }

    // Setting up playern names
   player1->setPlayerName(playerOneName);
   player2->setPlayerName(playerTwoName);
   if (threePlayerMode){
       player3->setPlayerName(playerThreeName);
   }

    lineBreak();
    std::cout << "Let's Play!" << '\n';
    lineBreak();


}

void playRound(Player* currentPlayer, Board* board, TilesBag* tilesBag, bool* qwirkleRowCheck, bool* qwirkleColCheck, Player* secondPlayer, Player* thirdPlayer) {
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
        if(currentPlayer->getPlayerHand()->getIndex(i)->getColourCode() == 'R'){
            std::cout <<RED_COLOR<<currentPlayer->getPlayerHand()->getIndex(i)->getTileCode() <<COLOUR_RESET<< ' ';
        }
        else if(currentPlayer->getPlayerHand()->getIndex(i)->getColourCode() == 'O'){
            std::cout <<ORANGE_COLOR<<currentPlayer->getPlayerHand()->getIndex(i)->getTileCode() <<COLOUR_RESET<< ' ';

        }else if(currentPlayer->getPlayerHand()->getIndex(i)->getColourCode() == 'Y'){
            std::cout <<YELLOW_COLOR<<currentPlayer->getPlayerHand()->getIndex(i)->getTileCode() <<COLOUR_RESET<< ' ';

        }else if(currentPlayer->getPlayerHand()->getIndex(i)->getColourCode() == 'G'){
            std::cout <<GREEN_COLOR<<currentPlayer->getPlayerHand()->getIndex(i)->getTileCode() <<COLOUR_RESET<< ' ';

        }else if(currentPlayer->getPlayerHand()->getIndex(i)->getColourCode() == 'B'){
            std::cout <<BLUE_COLOUR<<currentPlayer->getPlayerHand()->getIndex(i)->getTileCode() <<COLOUR_RESET<< ' ';

        }else if(currentPlayer->getPlayerHand()->getIndex(i)->getColourCode() == 'P'){
            std::cout <<PURPLE_COLOR<<currentPlayer->getPlayerHand()->getIndex(i)->getTileCode() <<COLOUR_RESET<< ' ';
        }
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
        if (command == "place" || command == "replace" || command == "save" || command == "help") { // checck the 1st command
            checkCommand = true;
        }
        
         /*
        1. if we use place or replce we trigger checkCommand true
        2. if its true, check for the first command, if its place then get the file name its its valid, check tile trigger true.
        3. get at command
        4. get cordinates and if valid, make checkcordinate true.
        5. 
        */
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
                std::cout << "Invalid Syntax; Please check for Typos" << '\n';
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
                std::cout << "Invalid Cordinates." << '\n';
            }


                //TODO making the and command and validate the command
            bool checkForLongCommand = false;
            std::string longCommand;
            bool checkAnd = false;

            if(commandStream >> longCommand && placeMoreTiles == true){
                checkForLongCommand = true;
                if (longCommand == "and") { 
                    checkAnd = true;
                }
            }
                //TODO make a new variable for 2nd tile string and validate
                bool checkSecondTile = false;
                bool secondCheckAt = false;
                bool secondCheckCoordinate = false;
                std::string secondTileString;
                std::string secondAt;
                std::string secondCoordinate;
                char secondRow;
                int secondCol = 0;

                if(checkForLongCommand){
                    commandStream >> secondTileString;
                    if (currentPlayer->getPlayerHand()->getData(secondTileString) != nullptr) { 
                        // check if tile exists in player's hand
                        checkSecondTile = true;
                    }

                //TODO check the second AT and validate 
                    commandStream >> secondAt;
            
                    if (secondAt == "at") { 
                        secondCheckAt = true;
                    }
                    else {
                        std::cout << "Invalid Syntax; Please check for Typos" << '\n';
                        checkSuccess = false;
                        placeSuccess = false;
                    }  

                //TODO now read the second cordinates, validte and add
                
                    commandStream >> secondCoordinate;
                    secondRow = secondCoordinate[0];
                    std::string secondColSub = secondCoordinate.substr(1);
                    std::stringstream secondColStr(secondColSub);
                    secondColStr >> secondCol;
                // row-65 == char to int coversion - (int) someChar
                    if ((secondRow-65) >= 0 && (secondRow-65) <= 25 && secondCol >= 0 && secondCol <= 25) { // check if the row and col are correct
                        secondCheckCoordinate = true;
                    }
                    else{
                        std::cout << "Invalid Cordinates." << '\n';
                        checkSuccess = false;
                        placeSuccess = false;
                    }
                }
            
     
            if (checkTile && checkAt && checkCoordinate && checkSecondTile && checkAnd && secondCheckAt && secondCheckCoordinate) { // all correct
                    // check if the tile was placed successfully > then add points
                bool placedSuccess = false;
                //TODO make a new bool for second placement 
                bool placeSecondSuccess = false;
                int pointsToGain = 0;
                placedSuccess = board->placeTile(currentPlayer->getPlayerHand()->getData(tileString), row, col, qwirkleRowCheck, qwirkleColCheck, pointsToGain);

                // TODO do the 2nd placement here 
                placeSecondSuccess = board->placeTile(currentPlayer->getPlayerHand()->getData(secondTileString), secondRow, secondCol, qwirkleRowCheck,qwirkleColCheck,pointsToGain);

                if (placedSuccess && placeSecondSuccess) {
                    currentPlayer->setPlayerPoints(currentPlayer->getPlayerPoints() + pointsToGain);
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
                if (placedSuccess && placeSecondSuccess) {
                    checkSuccess = true; // if success this big loop terminates
                    std::cout << "Your hand at end of turn is: " << std::endl;
                    for (int i = 0; i < currentPlayer->getPlayerHand()->getSize(); i++) {
                        std::cout << currentPlayer->getPlayerHand()->getIndex(i)->getTileCode() << ' ';
                    }
                }
                    std::cout << std::endl;
            }
            else if(checkTile && checkAt && checkCoordinate){
                bool placedSuccess = false;
                //TODO make a new bool for second placement 
                int pointsToGain = 0;
                placedSuccess = board->placeTile(currentPlayer->getPlayerHand()->getData(tileString), row, col, qwirkleRowCheck, qwirkleColCheck, pointsToGain);
        

                if (placedSuccess) {
                    currentPlayer->setPlayerPoints(currentPlayer->getPlayerPoints() + pointsToGain);
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
        
        else if (command == "save") {
            std::string saveName = "";
            commandStream >> saveName;
            if(threePlayerMode){
                saveGame(currentPlayer, secondPlayer, thirdPlayer, board, saveName, tilesBag->getTiles(),currentPlayer->getPlayerName());
            }
            else {
                saveGame(currentPlayer, secondPlayer, board, saveName, tilesBag->getTiles(),currentPlayer->getPlayerName());
            }
                
        }
        else if (command == "help"){

            if(helpMode){
                lineBreak();
                lineBreak();
                std::cout << "You have 3 options to choose from, Place|Replace|Save " << '\n';
                std::cout << "You can place a tile on the board using the command, place " << '\n';
                std::cout << "Use this format to place a tile, place <tile> at <positions> " << '\n';
                std::cout << "Eg: place R3 at B3 " << '\n';
                lineBreak();
                lineBreak();
                std::cout << "You can replace a tile on your hand using the command, replace " << '\n';
                std::cout << "Use this format to replace a tile, replace <tile> " << '\n';
                std::cout << "Eg: replace R3 " << '\n';
                lineBreak();
                lineBreak();
                std::cout << "You can save your current game using the command, save " << '\n';
                std::cout << "Use this format to replace a tile, save <filename> " << '\n';
                std::cout << "Eg: save newFile " << '\n';
                lineBreak();
            }
            else {
                std::cout << "Sorry!! Help mode is not turned ON. " << '\n';
                std::cout << "Please save the game, restart and choose option 5 to turn on enhancements " << '\n';
            }
        }

        else {
            checkSuccess = false;
            placeSuccess = false;
        }
    }
        
        if (!checkSuccess) {
            if (command != "save" && !std::cin.eof() && placeSuccess == false) {
                if(threePlayerMode){
                    std::cout << "Follow the Syntax form of place <firstTile> at <firstCordinate> and <secondTile> at <secondCordinate>" << std::endl;
                    std::cout << std::endl;
                }
                else{
                    std::cout << "Follow the Syntax form of 'place <Tile> at <Cordinate>" << std::endl;
                    std::cout << std::endl;
                }
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
    std::cout << "Enter the filename from which load a game " << '\n';
    std::string line;
    std::ifstream myfile;

    // Enhancement mode: adding help section to guide on loading a game
    do
    {
        std::cout << ">";
        std::cin >> userInputFileName;
        if(userInputFileName == "help"){
            std::cout  << '\n';
            std::cout  << '\n';
            std::cout << "Choose a game file from your computer to load" << '\n';
            std::cout << "Simply give the file path and press enter to continue..." << '\n';
            std::cout << "Eg: TestFiles/SavedGames/game3" << '\n';
        }
        else {
        perror("Error open");
            std::cout  << '\n';
            std::cout << "Game Load Unsuccessful! Please check your file again.." << '\n';
            std::cout  << '\n';
        }

    myfile.open(userInputFileName);

    } while (!myfile.is_open());
    
    int index = 0;
    while(getline(myfile, line)) {
        if (index == 0 && isInputValid(line)){
            player1->setPlayerName(line);  
            
        } 
        else if (index == 1) {
            int p1point;
            std::stringstream stream(line);
            stream >> p1point;
            player1->setPlayerPoints(p1point);
            
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

        } 
        else if (index == 3 && isInputValid(line)) {
            player2->setPlayerName(line);
        } 
        else if (index == 4) {
            int p2point;
            std::stringstream stream(line);
            stream >> p2point;
            player2->setPlayerPoints(p2point);
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
        } 
        else if (index == 6) {

            
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
        }
        else {
        } 
        index++;
    }
    

    std::cout << userInputFileName << " has been loaded Successfully ! " << std::endl;
    // Adding some line space
    std::cout << std::string( 10, '\n' );

};




void loadGame(Player* player1, Player* player2, Player* player3, Board* board, std::string fileName, LinkedList* tilesBag, int* turn, bool* qwirkleRowCheck, bool* qwirkleColCheck){

    
    std::string userInputFileName;
    std::cout << "Enter the filename from which load a game " << '\n';
    std::string line;
    std::ifstream myfile;

    // Enhancement mode: adding help section to guide on loading a game
    do
    {
        std::cout << ">";
        std::cin >> userInputFileName;
        if(helpMode == true && userInputFileName == "help"){
            std::cout  << '\n';
            std::cout  << '\n';
            std::cout << "Choose a game file from your computer to load" << '\n';
            std::cout << "Simply give the file path and press enter to continue..." << '\n';
            std::cout << "Eg: TestFiles/SavedGames/game3" << '\n';
        }
        else if (myfile.bad()) {
        perror("Error open");
            std::cout  << '\n';
            std::cout << "Game Load Unsuccessful! Please check your file again.." << '\n';
            std::cout  << '\n';
        }

    myfile.open(userInputFileName);

    } while (!myfile.is_open());
    
    int index = 0;
    while(getline(myfile, line)) {
        if (index == 1 && isInputValid(line)){
            player1->setPlayerName(line);
        } 
        else if (index == 2) {
            int p1point;
            std::stringstream stream(line);
            stream >> p1point;
            player1->setPlayerPoints(p1point);
            
        } 
        else if (index == 3) {
            
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
        } 
        else if (index == 4 && isInputValid(line)) {
            player2->setPlayerName(line);
        } 
        else if (index == 5) {
            int p2point;
            std::stringstream stream(line);
            stream >> p2point;
            player2->setPlayerPoints(p2point);
        } 
        else if (index == 6) {
            
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

        } 
        else if (index == 7 && isInputValid(line)) {
            player3->setPlayerName(line);
        } 
        else if (index == 8) {
            int p3point;
            std::stringstream stream(line);
            stream >> p3point;
            player3->setPlayerPoints(p3point);
        } 
        else if (index == 9) {
            
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
                    player3->getPlayerHand()->addBack(new Tile(colourChar, numInt));
                }
            }
        }



        else if (index == 10) {
            
        } 
        else if (index == 11) {
            
            // board state
            std::stringstream stream(line);
            std::string object;
            while(getline(stream, object, ' '))
            {
                // The line passed though here will need to be an individual tile 
                
                board->placeTileString(object, qwirkleRowCheck, qwirkleColCheck);
            }
        } 
        else if (index == 12) {
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
            
        } 
        else if (index == 13) {
            // Made currentPlayer variable for testing purposes
            std::string currentPlayer ="";
            if (line == player1->getPlayerName().substr(0, line .size())) {
                currentPlayer = player1->getPlayerName();
                *turn = 1; 
            } else if (line  == player2->getPlayerName().substr(0, line.size())) {
                *turn = 2;
                currentPlayer = player2->getPlayerName();
            } else if (line  == player3->getPlayerName().substr(0, line.size())) {
                *turn = 3;
                currentPlayer = player3->getPlayerName();
            }
        }
        // else {
        //     std::cout << "INVALID" << std::endl;
        // } 
        index++;
    }
    

    std::cout << userInputFileName << " Game has been loaded Successfully with Player-3 Mode ON! " << std::endl;
    // Adding some line space
    std::cout << std::string( 5, '\n' );

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

// M3 implementation 
void saveGame(Player* player1, Player* player2, Player* player3, Board* board, std::string fileName, LinkedList* tilesBag, std::string currentPlayer ){
    std::string s = "3-Mode Player Game File";
    std::ofstream file;
    file.open(fileName, std::ios_base::app);

    file << s << std::endl;
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

    file << player3->getPlayerName() << std::endl;
    file << player3->getPlayerPoints() << std::endl;
    LinkedList* player3Hand = player3->getPlayerHand();
    for (int i = 0; i < player3Hand->getSize() ; i++){

        file << player3Hand->getIndex(i)->getTileCode();
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


bool isInputValid(std::string input) {
    
    bool toReturn = true;

    /* this for loop is checking if the input has any special characters,numbers or lowercase letters.
    If there are any non characters, the index will update with the position that triggers toReturn to false. 
    To begin, Making index to -1 as it will never go below 0 inside the loop
    */
    int index = -1;
   
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