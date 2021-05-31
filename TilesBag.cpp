#include "TilesBag.h"
#include "TileCodes.h"
#include <iostream>
#include <fstream>
#include <random>

#define MAX_NUM_OF_TILES_IN_HAND 6 // max number of tiles in player hand
 // the total number of tiles in the game

TilesBag::TilesBag() {
    tiles = new LinkedList();
}

TilesBag::~TilesBag() {
    delete tiles;
}

LinkedList* TilesBag::getTiles() {
    return tiles;
}

void TilesBag::setTiles(LinkedList* tiles) {
    this->tiles = tiles;
}

void TilesBag::shuffleBag(){
    LinkedList* shuffledBag = new LinkedList();
    std::random_device randomSeed;
    int i = 0;
    while (i < tiles->getSize()) {
        // Pick a random tile from the tilesbag
        std::uniform_int_distribution<int> uniform_dist(0, tiles->getSize() - 1);
        int randIndex = uniform_dist(randomSeed);

        if (tiles->getIndex(randIndex) != nullptr) {
            // move tiles to shuffled likedlist
            Tile* tile = new Tile(*tiles->getIndex(randIndex));
            shuffledBag->addBack(tile);
            tiles->deleteIndex(randIndex);
        }
    }
    delete tiles;
    tiles = shuffledBag;
}

bool TilesBag::readOneTile(std::ifstream& file, char* colour, int* shape) {

    //read colour in char formate
    char readColour = 'R';
    bool readSuccess = true;
    file >> readColour; // 

    if(readColour == 'R'){
        *colour = RED;
    }else if (readColour == 'O'){
        *colour = ORANGE;
    }else if (readColour == 'Y'){
        *colour = YELLOW;
    }else if (readColour == 'G'){
        *colour = GREEN;
    }else if (readColour == 'B'){
        *colour = BLUE;
    }else if (readColour == 'P'){
        *colour = PURPLE;
    }else{
        readSuccess = false;
        std::cout << "Incorrect color try again!" << std::endl;
    }

    //read shape in number formate
    int readShape = 1;
    file >> readShape;
    
    if(readShape == 1){
        *shape = CIRCLE;
    }else if (readShape == 2){
        *shape = STAR_4;
    }else if (readShape == 3){
        *shape = DIAMOND;
    }else if (readShape == 4){
        *shape = SQUARE;
    }else if (readShape == 5) {//
        *shape = STAR_6;
    }else if (readShape == 6){
        *shape = CLOVER;
    }else{
        readSuccess = false;
        std::cout << "Incorrect shape try again!" << std::endl;
    }

    return readSuccess;

}

void TilesBag::initBag(){
        std::string tilesBagFileName = "TilesBag.txt";
        std::ifstream file(tilesBagFileName);
        
        int numRead = 0;
        while(!file.eof() && numRead < NUM_OF_TILES) {
        char colour = 'R';
        int shape = 1;   
        bool readSuccess = false; 
        
        readSuccess = readOneTile(file, &colour, &shape);
        
            if (!file.eof() && readSuccess) {
                Tile* tile = new Tile(colour, shape);
                tiles->addBack(tile);
                ++numRead;
            }
        }   
}

void TilesBag::initBagForM3(){
    std::string tilesBagFileName = "advancedTilesBag.txt";
        std::ifstream file(tilesBagFileName);
        
        int numRead = 0;
        while(!file.eof() && numRead < NUM_OF_TILES_M3) {
        char colour = 'R';
        int shape = 1;   
        bool readSuccess = false; 
        
        readSuccess = readOneTile(file, &colour, &shape);
        
            if (!file.eof() && readSuccess) {
                Tile* tile = new Tile(colour, shape);
                tiles->addBack(tile);
                ++numRead;
            }
        }   
}

LinkedList* TilesBag::moveTileFromBagToPlayerHand(int numOfTiles) {
    LinkedList* playerHand = new LinkedList();
    for (int i = 0; i < numOfTiles; i++)
    {
        
        playerHand->addBack(new Tile(*tiles->getIndex(i)));
    }
    for (int i = 0; i < numOfTiles; i++)
    {
        
        tiles->deleteFront();
    }
     
    return playerHand;
    
}

void TilesBag::printBag() {
    for (int i = 0; i < tiles->getSize(); i++)
    {
        std::cout << "Tiles Bag: " << tiles->getIndex(i)->getColourCode() << tiles->getIndex(i)->getShapeCode() << std::endl;
    }
}

Tile* TilesBag::getAndRemoveRandom() {
    std::random_device randomSeed;
    std::uniform_int_distribution<int> uniform_dist(0, tiles->getSize() - 1);
    int randIndex = uniform_dist(randomSeed);

    Tile* takeOut = new Tile(*tiles->getIndex(randIndex));
    tiles->deleteIndex(randIndex);
    return takeOut;
}