#include <vector>
#include <queue>
#include <string>
using namespace std;
#include "player.hpp"
#include "card.hpp"
#pragma once
namespace ariel{
class Game
{
private:
    Player& player1_;
    Player& player2_;
    vector<Card> deck_;
    string lastTurn;
    queue<string> log;
    int numOfTurns;
    int numOfTies;
public:
    Game( Player& player1 , Player& player2);
    
    void makeDeck();
    void shuffle();
    void divide();
    void setLasTurn(string turn);
    void setLog(string turn);
    void playTurn();
    void printLastTurn();
    void playAll();
    void printWiner();
    void printLog(); // prints all the turns played one line per turn (same format as game.printLastTurn())
    void printStats();
};
}