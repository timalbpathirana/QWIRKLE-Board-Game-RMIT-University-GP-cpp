#include "Board.h"
#include <stdlib.h>

Board::Board() {
    tilesOnBoard = 0;
    playingBoard.resize(BOARD_DIM);
    for (int i = 0; i < BOARD_DIM; i++) {
        rowsInfo[i] = "";
        rowsAmount[i] = 0;
        colsInfo[i] = "";
        colsAmount[i] = 0;
        playingBoard[i].resize(BOARD_DIM);
        for (int ii = 0; ii < BOARD_DIM; ii++) {
            playingBoard[i][ii] = nullptr;
        }
    }
};
Board::~Board() {
    for(int i= 0; i < BOARD_DIM; i++){
        for(int y = 0; y < BOARD_DIM; y++){
            if(playingBoard[i][y] != nullptr){
                delete playingBoard[i][y];
            }
        }
    }
};

bool Board::placeTile(Tile* tile, char rowChar, int col, bool* qwirkleRow, bool* qwirkleCol, int& playerPoints) {
    bool toReturn = false;
    int row = charToInt(rowChar);
    // if there is no tile yet, then no need to check anything
    if (tilesOnBoard == 0) {
        playingBoard[row][col] = tile; //->getTileCode();
        tilesOnBoard++;
        rowsAmount[row]++;
        colsAmount[col]++;
        toReturn = true;
        placedTiles.push_back(tile->getTileCode() + '@' + intToChar(row) + std::to_string(col));
    } else {
        if (!checkTileExists(tile, row, col) && checkTileNear(row, col) && playingBoard[row][col] == nullptr) {
            int rowCheck = 0;
            int colCheck = 0;

            Tile* leftSide = nullptr; Tile* rightSide = nullptr; Tile* upSide = nullptr; Tile* downSide = nullptr;
            if (col > 0 && col < 25) {
                leftSide = playingBoard[row][col-1];
                rightSide = playingBoard[row][col+1];
            } else if (col == 25) {
                leftSide = playingBoard[row][col-1];
            } else if (col == 0) {
                rightSide = playingBoard[row][col+1];
            }
            if (row > 0 && row < 25) {
                upSide = playingBoard[row-1][col];
                downSide = playingBoard[row+1][col];
            } else if (row == 25) {
                upSide = playingBoard[row-1][col];
            } else if (row == 0) {
                downSide = playingBoard[row+1][col];
            }

            if (rowsAmount[row] == 0) { // no tile on the entire row = ok
                rowCheck = 1;
            } else if (rowsAmount[row] != 0) {
                if (leftSide == nullptr && rightSide == nullptr) { // left and right are empty = ok
                    rowCheck = 2;
                } else if (leftSide != nullptr && rightSide != nullptr) { // left and right are filled
                    if (leftSide->getRowRule() == rightSide->getRowRule()) { // they are on same rule
                        if (leftSide->getRowRule() != "") { // check if the rule is not empty
                            if (leftSide->getRowRule()[0] == 'C') {
                                if (tile->getColourCode() == leftSide->getRowRule()[1]) { // side filled + rule and same colour
                                    rowCheck = 3;
                                }
                            } else if (leftSide->getRowRule()[0] == 'S') {
                                if (tile->getShapeCode() == leftSide->getRowRule()[1]) { // side filled + rule and same shape
                                    rowCheck = 4;
                                }
                            }
                        } else { // the rule is empty - check them if they are the same in some way
                            if (leftSide->getColourCode() == rightSide->getColourCode()) { // sides same color
                                if (tile->getColourCode() == leftSide->getColourCode()) {
                                    rowCheck = 5;
                                }
                            } else if (leftSide->getShapeCode() == rightSide->getShapeCode()) { // sides same shape
                                if (tile->getShapeCode() == leftSide->getShapeCode()) {
                                    rowCheck = 6;
                                }
                            }
                        }
                    } else { // the sides are not on the same rule
                        if (leftSide->getRowRule() == "") { // sides filled, not same rule, but left has no rule
                            if (rightSide->getRowRule()[0] == 'C' && leftSide->getColourCode() == rightSide->getRowRule()[1]) {
                                if (tile->getColourCode() == rightSide->getRowRule()[1]) {
                                    rowCheck = 7;
                                }
                            } else if (rightSide->getRowRule()[0] == 'S' && leftSide->getShapeCode()+'0' == rightSide->getRowRule()[1]) {
                                if (tile->getShapeCode()+'0' == rightSide->getRowRule()[1]) {
                                    rowCheck = 8;
                                }
                            }
                        } else if (rightSide->getRowRule() == "") { // sides filled, not same rule, but right has no rule
                            if (leftSide->getRowRule()[0] == 'C' && rightSide->getColourCode() == leftSide->getRowRule()[1]) {
                                if (tile->getColourCode() == leftSide->getRowRule()[1]) {
                                    rowCheck = 9;
                                }
                            } else if (leftSide->getRowRule()[0] == 'S' && rightSide->getShapeCode()+'0' == leftSide->getRowRule()[1]) {
                                if (tile->getShapeCode()+'0' == leftSide->getRowRule()[1]) {
                                    rowCheck = 10;
                                }
                            }
                        }
                    }
                } else if ((leftSide != nullptr && rightSide == nullptr) || (col == 25 && leftSide != nullptr) ) { // only left is filled
                    // std::cout << "THIS GUY HERE" << std::endl;
                    if (leftSide->getRowRule() == "") { // if that left tile has NO RULE yet 
                        if (tile->getColourCode() == leftSide->getColourCode()) { // same colour no rule
                            rowCheck = 11;
                        } else if (tile->getShapeCode() == leftSide->getShapeCode()) { // same shape no rule
                            rowCheck = 12;
                        }
                    } else { // that left tile has a rule
                        if (leftSide->getRowRule()[0] == 'C') { // if rule is Colour
                            if (tile->getColourCode() == leftSide->getRowRule()[1]) {
                                rowCheck = 13;
                            }
                        } else if (leftSide->getRowRule()[0] == 'S') { // if rule is Shape
                            if (tile->getShapeCode()+'0' == leftSide->getRowRule()[1]) {
                                rowCheck = 14;
                            }
                        }
                    }
                } else if ((rightSide != nullptr && leftSide == nullptr) || (col == 0 && rightSide != nullptr) ) { // only right is filled
                    if (rightSide->getRowRule() == "") { // if that right tile has NO RULE yet 
                        if (tile->getColourCode() == rightSide->getColourCode()) { // same colour no rule
                            rowCheck = 15;
                        } else if (tile->getShapeCode() == rightSide->getShapeCode()) { // same shape no rule
                            rowCheck = 16;
                        }
                    } else { // that right tile has a rule
                        if (rightSide->getRowRule()[0] == 'C') { // if rule is Colour
                            if (tile->getColourCode() == rightSide->getRowRule()[1]) {
                                rowCheck = 17;
                            }
                        } else if (rightSide->getRowRule()[0] == 'S') { // if rule is Shape
                            if (tile->getShapeCode()+'0' == rightSide->getRowRule()[1]) {
                                rowCheck = 18;
                            }
                        }
                    }
                }
            }

            if (colsAmount[col] == 0) { // no tile in the entire column
                colCheck = 1;
            } else if (colsAmount[col] != 0) { 
                if (upSide == nullptr && downSide == nullptr) { // up and down are empty = ok
                    colCheck = 2;
                } else if (upSide != nullptr && downSide != nullptr) { // both up and down are filled
                    if (upSide->getColRule() == downSide->getColRule()) { // check if they are on the same rule
                        if (upSide->getColRule() != "") { // check if the rule is not empty
                            if (upSide->getColRule()[0] == 'C') {
                                if (tile->getColourCode() == upSide->getColRule()[1]) { // side filled + rule and same colour
                                    colCheck = 3;
                                }
                            } else if (upSide->getColRule()[0] == 'S') {
                                if (tile->getShapeCode() == upSide->getColRule()[1]) { // side filled + rule and same shape
                                    colCheck = 4;
                                }
                            }
                        } else { // the rule is empty - check them if they are the same in some way
                            if (upSide->getColourCode() == downSide->getColourCode()) { // same color
                                if (tile->getColourCode() == upSide->getColourCode()) {
                                    colCheck = 5;
                                }
                            } else if (upSide->getShapeCode() == downSide->getShapeCode()) { // same shape
                                if (tile->getShapeCode() == upSide->getShapeCode()) {
                                    colCheck = 6;
                                }
                            }
                        }
                    } else { // the up and down are not on the same rule
                        if (upSide->getColRule() == "") { // up down filled, not same rule, but up has no rule
                            if (downSide->getColRule()[0] == 'C' && upSide->getColourCode() == downSide->getColRule()[1]) {
                                if (tile->getColourCode() == downSide->getColRule()[1]) {
                                    colCheck = 7;
                                }
                            } else if (downSide->getColRule()[0] == 'S' && upSide->getShapeCode()+'0' == downSide->getColRule()[1]) {
                                if (tile->getShapeCode()+'0' == downSide->getColRule()[1]) {
                                    colCheck = 8;
                                }
                            }
                        } else if (downSide->getColRule() == "") { // up down filled, not same rule, but down has no rule
                            if (upSide->getColRule()[0] == 'C' && downSide->getColourCode() == upSide->getColRule()[1]) {
                                if (tile->getColourCode() == upSide->getColRule()[1]) {
                                    colCheck = 9;
                                }
                            } else if (upSide->getColRule()[0] == 'S' && downSide->getShapeCode()+'0' == upSide->getColRule()[1]) {
                                if (tile->getShapeCode()+'0' == upSide->getColRule()[1]) {
                                    colCheck = 10;
                                }
                            }
                        }
                    }
                } else if ( (upSide != nullptr && downSide == nullptr) || (row == 25 && upSide != nullptr) ) { // if only up is filled
                    if (upSide->getColRule() == "") { // if that up tile has NO RULE yet
                        if (tile->getColourCode() == upSide->getColourCode()) { // same colour no rule
                            colCheck = 11;
                        } else if (tile->getShapeCode() == upSide->getShapeCode()) { // same shape no rule
                            colCheck = 12;
                        }
                    } else { // that up tile has a rule
                        if (upSide->getColRule()[0] == 'C') { // if rule is Colour
                            if (tile->getColourCode() == upSide->getColRule()[1]) {
                                colCheck = 13;
                            }
                        } else if (upSide->getColRule()[0] == 'S') { // if rule is Shape
                            if (tile->getShapeCode()+'0' == upSide->getColRule()[1]) {
                                colCheck = 14;
                            }
                        }
                    }
                } else if ((downSide != nullptr && upSide == nullptr) || (row == 0 && downSide != nullptr) ) { // if only down is filled
                    if (downSide->getColRule() == "") { // if that down tile has NO RULE yet 
                        if (tile->getColourCode() == downSide->getColourCode()) { // same colour no rule
                            colCheck = 15;
                        } else if (tile->getShapeCode() == downSide->getShapeCode()) { // same shape no rule
                            colCheck = 16;
                        }
                    } else { // that down tile has a rule
                        if (downSide->getColRule()[0] == 'C') { // if rule is Colour
                            if (tile->getColourCode() == downSide->getColRule()[1]) {
                                colCheck = 17;
                            }
                        } else if (downSide->getColRule()[0] == 'S') { // if rule is Shape
                            if (tile->getShapeCode()+'0' == downSide->getColRule()[1]) {
                                colCheck = 18;
                            }
                        }
                    }
                }
            }

            // the rowCheck and colCheck are both ok -> add the tile
            if (rowCheck != 0 && colCheck != 0) {
                playingBoard[row][col] = tile;//->getTileCode();
                tilesOnBoard++;
                rowsAmount[row]++;
                colsAmount[col]++;
                toReturn = true;
                placedTiles.push_back(tile->getTileCode() + '@' + intToChar(row) + std::to_string(col));

                // add the rule for the tile and neighbouring tiles if needed to
                if (rowCheck == 3 || rowCheck == 4) {
                    tile->setRowRule(leftSide->getRowRule());
                } else if (rowCheck == 5 || rowCheck == 6 || rowCheck == 11 || rowCheck == 12 || rowCheck == 15 || rowCheck == 16) {
                    std::string toAdd;
                    if (rowCheck == 5 || rowCheck == 11 || rowCheck == 15) {
                        toAdd += 'C'; toAdd += tile->getColourCode();
                    } else if (rowCheck == 6 || rowCheck == 12 || rowCheck == 16) {
                        toAdd += 'S'; toAdd += tile->getShapeCode()+'0';
                    }
                    tile->setRowRule(toAdd);

                    if (rowCheck == 5 || rowCheck == 6 || rowCheck == 11 || rowCheck == 12) {
                        leftSide->setRowRule(tile->getRowRule());
                    }
                    if (rowCheck == 5 || rowCheck == 6 || rowCheck == 15 || rowCheck == 16) {
                        rightSide->setRowRule(tile->getRowRule());
                    }
                } else if (rowCheck == 7 || rowCheck == 8 || rowCheck == 17 || rowCheck == 18) {
                    tile->setRowRule(rightSide->getRowRule());
                    if (rowCheck == 7 || rowCheck == 8) {
                        leftSide->setRowRule(tile->getRowRule());
                    }
                } else if (rowCheck == 9 || rowCheck == 10 || rowCheck == 13 || rowCheck == 14) {
                    tile->setRowRule(leftSide->getRowRule());
                    if (rowCheck == 9 || rowCheck == 10) {
                        rightSide->setRowRule(tile->getRowRule());
                    }
                }

                if (colCheck == 3 || colCheck == 4) {
                        tile->setColRule(upSide->getColRule());
                } else if (colCheck == 5 || colCheck == 6 || colCheck == 11 || colCheck == 12 || colCheck == 15 || colCheck == 16) {
                    std::string toAdd;
                    if (colCheck == 5 || colCheck == 11 || colCheck == 15) {
                        toAdd += 'C'; toAdd += tile->getColourCode();
                    } else if (colCheck == 6 || colCheck == 12 || colCheck == 16) {
                        toAdd += 'S'; toAdd += tile->getShapeCode()+'0';
                    }
                    tile->setColRule(toAdd);

                    if (colCheck == 5 || colCheck == 6 || colCheck == 11 || colCheck == 12) {
                        upSide->setColRule(tile->getColRule());
                    }
                    if (colCheck == 5 || colCheck == 6 || colCheck == 15 || colCheck == 16) {
                        downSide->setColRule(tile->getColRule());
                    }
                } else if (colCheck == 7 || colCheck == 8 || colCheck == 17 || colCheck == 18) {
                    tile->setColRule(downSide->getColRule());
                    if (colCheck == 7 || colCheck == 8) {
                        upSide->setColRule(tile->getColRule());
                    }
                } else if (colCheck == 9 || colCheck == 10 || colCheck == 13 || colCheck == 14) {
                        tile->setColRule(upSide->getColRule());
                    if (colCheck == 9 || colCheck == 10) {
                        downSide->setColRule(tile->getColRule());
                    }
                }

                // check for qwirkle
                // row
                int rowCount = 1;
                for (int i = col+1; i < BOARD_DIM && playingBoard[row][i] != nullptr; i++) {
                    rowCount++;
                }
                for (int i = col-1; i >= 0 && playingBoard[row][i] != nullptr; i--) {
                    rowCount++;
                }
                if (rowCount == 6) {
                    // std::cout << "QWIRKLE! at: " << tile->getTileCode() << std::endl;
                    *qwirkleRow = true;
                }
                playerPoints = playerPoints + ((rowCount - 1) * 2);

                // col
                int colCount = 1;
                for (int i = row+1; i < BOARD_DIM && playingBoard[i][col] != nullptr; i++) {
                    colCount++;
                }
                for (int i = row-1; i >= 0 && playingBoard[i][col] != nullptr; i--) {
                    colCount++;
                }
                if (colCount == 6) {
                    // std::cout << "QWIRKLE! at: " << tile->getTileCode() << std::endl;
                    *qwirkleCol = true;
                }
                playerPoints = playerPoints + ((colCount - 1) * 2);
            }
        }
    }
    return toReturn;
};

bool Board::checkTileExists(Tile* tile, int row, int col) {
    bool toReturn = false;

    bool rowCheck = false;
    for (int i = col+1; i < BOARD_DIM && playingBoard[row][i] != nullptr; i++) {
        if (tile->getTileCode() == playingBoard[row][i]->getTileCode()) {
            rowCheck = true;
        }
    }
    for (int i = col-1; i >= 0 && playingBoard[row][i] != nullptr; i--) {
        if (tile->getTileCode() == playingBoard[row][i]->getTileCode()) {
            rowCheck = true;
        }
    }

    bool colCheck = false;
    for (int i = row+1; i < BOARD_DIM && playingBoard[i][col] != nullptr; i++) {
        if (tile->getTileCode() == playingBoard[i][col]->getTileCode()) {
            colCheck = true;
        }
    }
    for (int i = row-1; i >= 0 && playingBoard[i][col] != nullptr; i--) {
        if (tile->getTileCode() == playingBoard[i][col]->getTileCode()) {
            colCheck = true;
        }
    }

    if (rowCheck || colCheck) {
        toReturn = true;
    }
    return toReturn;
};
bool Board::checkTileNear(int row, int col) {
    bool toReturn = false;
    if (col != 0 && playingBoard[row][col-1] != nullptr) {
        toReturn = true;
    } else if (col != 25 && playingBoard[row][col+1] != nullptr) {
        toReturn = true;
    } else if (row != 0 && playingBoard[row-1][col] != nullptr) {
        toReturn = true;
    } else if (row != 25 && playingBoard[row+1][col] != nullptr) {
        toReturn = true;
    }
    return toReturn;
};

void Board::printPlayingBoard() {
    if (tilesOnBoard == 0) {
        std::cout << "A0..........A25" << std::endl;
        std::cout << ".             ." << std::endl;
        std::cout << ".             ." << std::endl;
        std::cout << ".             ." << std::endl;
        std::cout << ".             ." << std::endl;
        std::cout << ".             ." << std::endl;
        std::cout << "Z0..........Z25" << std::endl << std::endl;
    } else {
        int left = 100;
        int top = 100;
        int right = -100;
        int bottom = -100;

        for (int i = 0; i < BOARD_DIM; i++) {
            for (int ii = 0; ii < BOARD_DIM; ii++) {
                if (playingBoard[i][ii] != nullptr) {
                    if (ii < left) {
                        left = ii;
                    }
                    if (ii > right) {
                        right = ii;
                    }
                    if (i < top) {
                        top = i;
                    }
                    if (i > bottom) {
                        bottom = i;
                    }
                }
            }
        }


        int topStart = 0;
        if (top - 1 > 0) {
            topStart = top - 1;
        }
        int leftStart = 0;
        if (left - 1 > 0) {
            leftStart = left - 1;
        }
        int bottomEnd = BOARD_DIM - 1;
        if (bottom + 1 < BOARD_DIM - 1) {
            bottomEnd = bottom + 1;
        }
        int rightEnd = BOARD_DIM - 1;
        if (right + 1 < BOARD_DIM - 1) {
            rightEnd = right + 1;
        }

        for (int i = topStart-2; i <= bottomEnd; i++) {
            // std::cout << '|';
            for (int ii = leftStart-1; ii <= rightEnd; ii++) {
                if (i == topStart - 2) {
                    if (ii != leftStart - 1) {
                        if (ii < 10) {
                            std::cout << "  " << ii;
                        } else {
                            std::cout << ' ' << ii;
                        }
                    } else {
                        std::cout << " ";
                    }
                } else if (i == topStart - 1) {
                    if (ii != leftStart - 1) {
                        std::cout << "---";
                    } else {
                        std::cout << "   ";
                    }
                } else {
                    if (ii == leftStart - 1) {
                        std::cout << intToChar(i)  << " |";
                    } else {
                        if (playingBoard[i][ii] != nullptr) {
                            
                            if(playingBoard[i][ii]->getColourCode() == 'R'){
                                std::cout <<RED_COLOR<<playingBoard[i][ii]->getTileCode() <<COLOUR_RESET<< '|';

                            }else if(playingBoard[i][ii]->getColourCode() == 'O'){
                                std::cout <<ORANGE_COLOR<<playingBoard[i][ii]->getTileCode() <<COLOUR_RESET<< '|';

                            }else if (playingBoard[i][ii]->getColourCode() == 'Y') {
                                std::cout <<YELLOW_COLOR<<playingBoard[i][ii]->getTileCode() <<COLOUR_RESET<< '|';

                            }else if (playingBoard[i][ii]->getColourCode() == 'G') {
                                std::cout <<GREEN_COLOR<<playingBoard[i][ii]->getTileCode() <<COLOUR_RESET<< '|';

                            }else if (playingBoard[i][ii]->getColourCode() == 'B') {
                                std::cout <<BLUE_COLOUR<<playingBoard[i][ii]->getTileCode() <<COLOUR_RESET<< '|';

                            }else if (playingBoard[i][ii]->getColourCode() == 'P') {
                                std::cout <<PURPLE_COLOR<<playingBoard[i][ii]->getTileCode() <<COLOUR_RESET<< '|';
                            }   
                        } else {
                            std::cout << "  |";
                        }
                    }
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};





char Board::intToChar(int num) {
    char toReturn = num + 65;
    return toReturn;
}

int Board::charToInt(char letter) {
    int toReturn = letter - 65;
    return toReturn;
}

int Board::getHeight() {
    int toReturn = 0;
    for (int i = 0; i < BOARD_DIM; i++) {
        if (colsAmount[i] > toReturn) {
            toReturn = colsAmount[i];
        }
    }
    return toReturn;
}

int Board::getWidth() {
    int toReturn = 0;
    for (int i = 0; i < BOARD_DIM; i++) {
        if (rowsAmount[i] > toReturn) {
            toReturn = rowsAmount[i];
        }
    }
    return toReturn;
}

std::vector<std::string> Board::getplacedTiles() {
    return placedTiles;
}

bool Board::placeTileString(std::string tileString, bool* qwirkleRow, bool* qwirkleCol) {
    std::string tileCode = tileString.substr(0, 2);
    std::string posCode = tileString.substr(3);
    char row = posCode[0];
    std::string posCodeSub = posCode.substr(1);
    std::stringstream posStream(posCodeSub);
    int col; posStream >> col;
    Tile* newTile = new Tile(tileCode[0], tileCode[1]-'0');
    int i = 0;
    
    return placeTile(newTile, row, col, qwirkleRow, qwirkleCol,i);
}