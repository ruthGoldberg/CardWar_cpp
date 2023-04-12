#include "player.hpp"
#include "card.hpp"
#include <string>
using namespace ariel;

Player::Player(string name){
    this->name = name;
    this->winTurn = 0;
    this->isInGame = false;
}
void Player::addMyCards(Card& card){
    myCards.push_back(card);
}
void Player::addCardsTaken(Card& card1){
    gaindCards.push_back(card1);
}
Card& Player::throwCard(){
    Card& temp = myCards.back();
    myCards.pop_back();
    return temp; 
}
int Player::stacksize(){
    return myCards.size(); 
}
int Player::cardesTaken(){
    return gaindCards.size();
}
string Player::getName()const{
    return name;
}
string Player::getCardsWon(){
    string cards ="";
    while(!cardsWon.empty()){
        cards += cardsWon.front()+ " | ";
        cardsWon.pop();
    }
    return cards;
}

    