#ifndef TOWN_HALL
#define TOWN_HALL

#include <iostream>
#include "Cart_Point.h"
#include "Game_Object.h"
using namespace std;

class Town_Hall: public Game_Object
{
public:
    Town_Hall();
    ~Town_Hall();
    Town_Hall(int, Cart_Point);
    Cart_Point get_location();
    void deposit_gold(double);
    bool update();
    void show_status();
    void save(ofstream&);
    void restore(ifstream&);
    double get_amount();
    class Model;

private:
    double amount;
};
#endif // TOWN_HALL

