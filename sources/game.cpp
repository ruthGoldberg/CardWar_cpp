//got the randon shuffle method from https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
//learn about exception : https://www.tutorialspoint.com/cplusplus/cpp_exceptions_handling.htm
#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <algorithm>
#include <random>
#include "game.hpp"
#include "card.hpp"
using namespace std;
using namespace ariel;

Game::Game ( Player& player1,  Player& player2):player1_(player1) , player2_(player2){
    if(player1.getInGame())
        throw "Player 1 is already in a game";
    if(player2.getInGame())
        throw "Player 2 is already in a game";
    player1.setInGame(true);
    player2.setInGame(true);
    numOfTurns=0;
    numOfTies=0;
    lastTurn="";
    makeDeck();
}
void Game::makeDeck(){
    for(int i = 1; i<=13 ; i++){
        deck_.push_back(Card(i, "Hearts"));
        deck_.push_back(Card(i,"Spades"));
        deck_.push_back(Card(i,"Diamonds"));
        deck_.push_back(Card(i,"Clovers"));
    }
    shuffle();
}
void Game :: shuffle(){
    unsigned seed = (unsigned) time(NULL);
    auto range = default_random_engine(seed);
    std::shuffle(deck_.begin(), deck_.end(), range);
    divide();
}
void Game:: divide(){
    for(int i = 1; i <= 26 ; i++){
        player1_.addMyCards(deck_.back());
        deck_.pop_back();
        player2_.addMyCards(deck_.back());
        deck_.pop_back();

    }
}
void Game:: playTurn(){
    if(&player1_ == &player2_){
        throw "There is only one player";
        return;
    }
    static int count=0;
    static stack<Card> firstPlayerCards;
    static stack<Card> secondPlayerCards;
    static string lasTurn="";
    if(player1_.stacksize() == 0 ){
        if(count == 0){
            throw "No more cards left . GAME OVER!";
        }
        if(count > 0){
            while(!firstPlayerCards.empty()){
                player1_.addCardsTaken(firstPlayerCards.top());
                firstPlayerCards.pop();
            }
            while(!secondPlayerCards.empty()){
                player2_.addCardsTaken(secondPlayerCards.top());
                secondPlayerCards.pop();
            }
            count = 0;
        }
        player1_.setInGame(false) ;
        player2_.setInGame(false);
        return;
    }
    if(count == 0){
        numOfTurns++;
        lasTurn="";
    }
    if(count>0){
        firstPlayerCards.push(player1_.throwCard());
        secondPlayerCards.push(player2_.throwCard());
        if(player1_.stacksize() == 0 ){
            while(!firstPlayerCards.empty()){
            player1_.addCardsTaken(firstPlayerCards.top());
            firstPlayerCards.pop();
            }
            while(!secondPlayerCards.empty()){
            player2_.addCardsTaken(secondPlayerCards.top());
            secondPlayerCards.pop();
            }
            count = 0;
        return;
        }
    }
    firstPlayerCards.push(player1_.throwCard());
    secondPlayerCards.push(player2_.throwCard());
    int differ = firstPlayerCards.top().compare(secondPlayerCards.top());

    if(differ == 1){
        player2_.setWinTurn();
        player2_.setCardsWon(secondPlayerCards.top().toString());
        lasTurn += player1_.getName()+" played "
        +firstPlayerCards.top().toString()+" "+player2_.getName()+" played "+(secondPlayerCards.top()).toString()+". "
        +player2_.getName()+" wins.";
       
        while(!firstPlayerCards.empty()){
            player2_.addCardsTaken(firstPlayerCards.top());
            player2_.addCardsTaken(secondPlayerCards.top());
            firstPlayerCards.pop();
            secondPlayerCards.pop();
        }
    }
    if(differ == -1){
        player1_.setWinTurn();
        player1_.setCardsWon(firstPlayerCards.top().toString());
        

        lasTurn += player1_.getName()+" played "
        +firstPlayerCards.top().toString()+" "+player2_.getName()+" played "+(secondPlayerCards.top()).toString()+". "
        +player1_.getName()+" wins.";
        
        while(!firstPlayerCards.empty()){
            player1_.addCardsTaken(firstPlayerCards.top());
            player1_.addCardsTaken(secondPlayerCards.top());
            firstPlayerCards.pop();
            secondPlayerCards.pop();
        }

    }
    if(differ == 0){
        lasTurn += player1_.getName()+" played "
        +firstPlayerCards.top().toString()+" "+player2_.getName()+" played "+(secondPlayerCards.top()).toString()+". draw. ";
        numOfTies++;
        count++;
        playTurn();
        return;
    }
    if(count>0){
            count=0;
    }
    setLasTurn(lasTurn);

}
void Game::printLastTurn(){
    if(player1_.stacksize() == 26){
        throw "Game hasn't started yet ";
        return;
    }
    cout<<lastTurn<< "\n";
}
void Game::playAll(){
    while(player1_.stacksize() > 0){
        playTurn();
    }
    player1_.setInGame(false);
    player2_.setInGame(false);
}
void Game::printWiner(){
    if(player1_.stacksize() == 26 ){
        throw "Game hasn't started yet";
        return;
    }
    if(player1_.cardesTaken() > player2_.cardesTaken())
        cout<<player1_.getName()<<endl;
    else if(player1_.cardesTaken() < player2_.cardesTaken())
        cout<<player2_.getName()<<endl;
    else cout<<"Its a tie!"<<endl;
}
void Game::printLog(){
    if(player1_.stacksize() == 26){
        throw "Game hasn't started yet ";
        return;
    }
    while(!log.empty()){
        cout<<log.front()<<endl;
        log.pop();
    }

} 
void Game::printStats(){
    if(player1_.stacksize() == 26 ){
        throw "Game hasn't started yet";
        return;
    }
    cout<<numOfTurns<<endl;
    cout<<player1_.getWinTurn()<<endl;
    double playerOneWon = (double)player1_.getWinTurn()/numOfTurns;
    string cardsWon1=player1_.getCardsWon();

    string cardsWon2=player2_.getCardsWon();
    cout<<player2_.getWinTurn()<<endl;
    double playerTwoWon = (double)player2_.getWinTurn()/numOfTurns;
    double drawRate =(double) numOfTies/numOfTurns;

    cout<<"Player 1 ("+player1_.getName()+"): win rate - " << (double)playerOneWon <<" Cards won - "<<cardsWon1<<endl;
    cout<<"Player 2 ("+player2_.getName()+"): win rate - " << (double)playerTwoWon <<" Cards won - "<<cardsWon2<<endl;
    cout<<"Draw rate : "<<drawRate<<" amount of draws : "<<numOfTies<<endl;
}

void Game::setLasTurn(string turn){
    lastTurn = turn;
    setLog(turn);
}
void Game::setLog(string turn){
    log.push(turn);
}
