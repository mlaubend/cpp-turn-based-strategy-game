#ifndef GOLD_MINE.H
#define GOLD_MINE.H

#include <iostream>
#include "Cart_Point.h"
#include "Game_Object.h"
#include "Person.h"
#include "Town_Hall.h"

class Gold_Mine: public Game_Object
{
public:
    Gold_Mine();
    ~Gold_Mine();
    Gold_Mine(int, Cart_Point);
    Cart_Point get_location();
    bool is_empty();
    double dig_gold(double);
    bool update();
    void show_status();
    double get_amount();
    void save(ofstream&);
    void restore(ifstream&);

private:
    double amount;
};

#endif // GOLD_MINE
