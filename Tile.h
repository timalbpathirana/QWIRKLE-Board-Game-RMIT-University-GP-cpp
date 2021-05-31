#ifndef TILE_H
#define TILE_H

#include <string>
#include "TileCodes.h"

class Tile {
    public:
        /**
         * Tile constructor
         * input: 
         * colour code as char (R, O, Y, G, B, P)
         * shape code as int (1, 2, 3, 4, 5, 6)
         */
        Tile(char colourCode, int shapeCode);
        ~Tile();
        Tile(Tile& other);

        /**
         * output: shape code as int
         */
        int getShapeCode();
        /**
         * output: colour code as char
         */
        char getColourCode();

        /**
         * output: shape as string
         */
        std::string getShapeString();
        /**
         * output: colour as string
         */
        std::string getColourString();

        /**
         * output: tile as string (<ColourCode><ShapeCode>)
         */
        std::string getTileCode();

        std::string getRowRule();
        void setRowRule(std::string rowRule);
        std::string getColRule();
        void setColRule(std::string colRule);

    private:
        int shapeCode;
        char colourCode;

        std::string shapeString;
        std::string colourString;

        std::string rowRule;
        std::string colRule;
};

#endif // TILE_H