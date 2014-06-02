#ifndef MINER
#define MINER

#include <iostream>
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"
using namespace std;

class Miner: public Person
{
public:
    Miner();
    ~Miner();
    Miner(int, Cart_Point);
    bool update();
    bool update_location();
    void start_mining(Gold_Mine*, Town_Hall*);
    virtual void show_status();
    double get_amount();
    void save(ofstream&);
    void restore(ifstream&);
    void take_hit(int, Person*);

private:
    double amount;
    Gold_Mine* mine;
    Town_Hall* home;
};

#endif // MINER.H
