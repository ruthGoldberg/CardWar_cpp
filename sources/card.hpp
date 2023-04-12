#include <string>
#pragma once
using namespace std;
namespace ariel{
    class Card
    {
    private:
        int number_;
        string shape_;
    public:
        Card(int number , string shape);
        int getNumber()const;
        string getShape()const;
        int compare (Card& other)const;
        string toString();

    };
}

