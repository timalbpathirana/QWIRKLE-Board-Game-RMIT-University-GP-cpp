#include "Player.h"

Player::Player(int playerNum, std::string playerName) {
    this->playerNum = playerNum;
    this->playerName = playerName;
    playerPoints = 0;
    playerHand = new LinkedList();
};
Player::Player(int playerNum) {
    this->playerNum = playerNum;
    playerName = "NULL";
    playerPoints = 0;
    playerHand = new LinkedList();
}
Player::~Player() {
    delete playerHand; 
};

int Player::getPlayerNum() {
    return playerNum;
}

std::string Player::getPlayerName() {
    return playerName;
}

LinkedList* Player::getPlayerHand() {
    return playerHand;
}

int Player::getPlayerPoints() {
    return playerPoints;
}

void Player::setPlayerName(std::string playerName){
    this->playerName = playerName;
}

void Player::setPlayerPoints(int playerPoints) {
    this->playerPoints = playerPoints;
}

void Player::setPlayerHand(LinkedList* playerHand) {
    this->playerHand = playerHand;
}