#include <string>
#include "card.hpp"
using namespace std;
using namespace ariel;

Card::Card(int number , string shape){
    number_= number;
    shape_=shape;
}
int Card::getNumber()const{
    return number_;
}
string Card:: getShape()const{
     return shape_;
}
int Card::compare (Card& other)const{
    if(number_ < other.getNumber()){ //return 1
       if(number_ == 1){
            if(other.getNumber() == 2)
                return 1;
            return -1;
       }
       return 1;
    }
    
    if(number_ > other.getNumber()){ //return -1
       if(other.getNumber() == 1){
            if(number_ == 2)
                return -1;
            return 1;
       }
       return -1;
    }
    return 0 ;
}
string Card::toString(){
    string kindOfCard="";
    switch (number_){
    case 11:
        kindOfCard = "Jack of "+shape_;
        break;
    case 12:
        kindOfCard = "Queen of "+shape_;
        break;
    case 13:
        kindOfCard = "King of "+shape_;
        break;
    default:
        kindOfCard = to_string( number_) +" of "+shape_;
        break;
    }
    return kindOfCard;
}