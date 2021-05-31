#include "Tile.h"

Tile::Tile(char colourCode, int shapeCode) {
    this->shapeCode = shapeCode;
    this->colourCode = colourCode;

    if (colourCode == RED) {
        colourString = "Red";
    } else if (colourCode == ORANGE) {
        colourString = "Orange";
    } else if (colourCode == YELLOW) {
        colourString = "Yellow";
    } else if (colourCode == GREEN) {
        colourString = "Green";
    } else if (colourCode == BLUE) {
        colourString = "Blue";
    } else if (colourCode == PURPLE) {
        colourString = "Purple";
    }

    if (shapeCode == CIRCLE) {
        shapeString = "Circle";
    } else if (shapeCode == STAR_4) {
        shapeString = "4-Star";
    } else if (shapeCode == DIAMOND) {
        shapeString = "Diamond";
    } else if (shapeCode == SQUARE) {
        shapeString = "Square";
    } else if (shapeCode == STAR_6) {
        shapeString = "6-Star";
    } else if (shapeCode == CLOVER) {
        shapeString = "Clover";
    }
};
Tile::~Tile() {};
Tile::Tile(Tile& other) {
    this->shapeCode = other.shapeCode;
    this->colourCode = other.colourCode;
    this->shapeString = other.shapeString;
    this->colourString = other.colourString;
    this->rowRule = other.rowRule;
    this->colRule = other.colRule;
}

int Tile::getShapeCode() {
    return shapeCode;
};
char Tile::getColourCode() {
    return colourCode;
};

std::string Tile::getShapeString() {
    return shapeString;
};
std::string Tile::getColourString() {
    return colourString;
};

std::string Tile::getTileCode() {
    return colourCode + std::to_string(shapeCode);
}

std::string Tile::getRowRule() {
    return rowRule;
}
void Tile::setRowRule(std::string rowRule) {
    this->rowRule = rowRule;
}
std::string Tile::getColRule() {
    return colRule;
}
void Tile::setColRule(std::string colRule) {
    this->colRule = colRule;
}