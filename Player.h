#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Tile.h"
#include "LinkedList.h"

class Player {
    public:
        /**
         * Player constructor
         * input:
         * playerNum as int
         * playerName as std::string
         */
        Player(int playerNum, std::string playerName);
        Player(int playerNum);
        ~Player();

        /**
         * output: playerNum as int
         */
        int getPlayerNum();
        /**
         * output: playerName as std::string
         */
        std::string getPlayerName();
        /**
         * output: playerHand as LinkedList*
         */
        LinkedList* getPlayerHand();
        /**
         * output: playerPoints as int
         */
        int getPlayerPoints();

        /**
         * set the player points
         * input: playerPoints as int
         * output: none
         */
        void setPlayerPoints(int playerPoints);

        /**
         * set player hand to an existing hand - for initial hand
         * input: playerHand as LinkedList*
         * output: none
         */
        void setPlayerHand(LinkedList* playerHand);

        /**
         * set player name to playerName
         * input: playerName as std::string
         * output: none
         */
        void setPlayerName(std::string playerName);

    private:
        int playerNum;
        std::string playerName;
        LinkedList* playerHand;
        int playerPoints;
};

#endif // PLAYER_H