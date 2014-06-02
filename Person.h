#ifndef PERSON.H
#define PERSON.H

#include <iostream>
#include "Game_Object.h"
#include "Cart_Point.h"
#include "Cart_Vector.h"

using namespace std;

class Person: public Game_Object
{
public:
    Person();
    virtual ~Person();
    Person(char);
    Person(char, int, Cart_Point);
    void start_moving(Cart_Point);
    virtual void start_mining();
    void stop();
    virtual void show_status();
    Cart_Point get_destination();
    void set_destination(Cart_Point);
    Cart_Vector get_delta();
    bool is_alive();
    virtual void take_hit(int, Person*);
    virtual void start_attack(Person*);
    double get_speed();
    int get_health();
    virtual void save(ofstream&);
    virtual void restore(ifstream&);

protected:
    bool update_location();
    void setup_destination(Cart_Point);

private:
    double speed;
    int health;
    Cart_Point destination;
    Cart_Vector delta;
};

#endif // PERSON
