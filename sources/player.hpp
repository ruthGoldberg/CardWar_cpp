#include <string>
#include <vector>
#include <queue>
using namespace std;
#pragma once
#include "card.hpp"
namespace ariel{

class Player
{
private:
    string name;
    bool isInGame;
    vector<Card> myCards;
    vector<Card> gaindCards;
    int winTurn;
    queue<string> cardsWon; 
public:
    Player(string name);
    void addMyCards(Card& card);
    void addCardsTaken(Card& card1);
    Card& throwCard();
    int stacksize();
    int cardesTaken();
    string getName()const;
    void setWinTurn(){
        winTurn++;
    }
    int getWinTurn()const{
        return winTurn;
    }
    void setCardsWon(string const &cardWon){
        cardsWon.push(cardWon);
    }

    string getCardsWon();

    bool getInGame()const{
        return isInGame;
    }
    void setInGame(bool isIn){
        this->isInGame = isIn;
    }

};
}

