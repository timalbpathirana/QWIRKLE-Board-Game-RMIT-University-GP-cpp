#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <sstream>
#include "TileCodes.h"
#include "Tile.h"
#include "Node.h"
#include "LinkedList.h"
#include "Player.h"
#include "TileCodes.h"


class Board {
    public:
        Board();
        ~Board();

        /**
         * place tile at row and col, return true if tile was placed successfully
         * input:
         * tile as Tile*
         * row as char
         * col as int
         * output: boolean
         */
        bool placeTile(Tile* tile, char rowChar, int col, bool* qwirkleRow, bool* qwirkleCol, int& playerPoints);

        /**
         * check if tile exists, return false in order for tile to be added
         * input:
         * tile as Tile*
         * row as int
         * col as int
         * output: boolean
         */
        bool checkTileExists(Tile* tile, int row, int col);
        /**
         * check if there is a tile next to the current row and col, return true for tile to be added
         * input:
         * row as int
         * col as int
         * output: boolean
         */
        bool checkTileNear(int row, int col);

        /**
         * print the playing board
         */
        void printPlayingBoard();

        /**
         * convert an int to char - for use when printing the board
         * input: int
         * output: char
         */
        char intToChar(int num);

        /**
         * convert an char to int - for use when placing tile
         * input: char
         * output: int
         */
        int charToInt(char letter);

        /**
         * get the height of the board - the row that is longest
         * output: int
         */
        int getHeight();

        /**
         * get the width of the board - the col that is longest
         * output: int
         */
        int getWidth();

        /**
         * return the vector containing placed tile in format: <TILE>@<COORDINATES>
         * input: none
         * output: std::vector
         */
        std::vector<std::string> getplacedTiles();

        /**
         * add tiles read from a text file, returns true if added successfully
         * intput: tiles and position in format: <TILE>@<COORDINATES>
         * output: bool
         */
        bool placeTileString(std::string tileString, bool* qwirkleRow, bool* qwirkleCol);


    private:
        int tilesOnBoard;
        std::vector<std::vector<Tile*> > playingBoard;
        std::string rowsInfo[BOARD_DIM];
        int rowsAmount[BOARD_DIM];
        std::string colsInfo[BOARD_DIM];
        int colsAmount[BOARD_DIM];
        std::vector<std::string> placedTiles;
};

#endif // BOARD_H