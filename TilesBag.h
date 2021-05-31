#ifndef TILESBAG_H
#define TILESBAG_H

#include "LinkedList.h"

class TilesBag {
  public:
    TilesBag();
    ~TilesBag();
    LinkedList* getTiles();
    void setTiles(LinkedList* tiles);
    bool readOneTile(std::ifstream& file, char* colour, int* shape);
    void initBag();
    LinkedList* moveTileFromBagToPlayerHand(int numOfTiles);
    void printBag();

    // changed methods
    // LinkedList* shuffleBag();
    void shuffleBag();
    Tile* getAndRemoveRandom();
  
  private:
        
    LinkedList* tiles;
};

#endif // ASSIGN2_TILEBAG_H
