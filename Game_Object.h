#ifndef GAME_OBJECT.H
#define GAME_OBJECT.H

#include <iostream>
#include "Cart_Point.h"
using namespace std;

class Game_Object
{
public:
    Game_Object();
    virtual ~Game_Object();
    Game_Object(char);
    Game_Object(char, int, Cart_Point);
    Cart_Point get_location();
    int get_id();
    virtual void show_status();
    void drawself(char*);
    char get_display_code();
    virtual bool update() = 0;
    virtual bool is_alive();
    virtual void save(ofstream&);
    virtual void restore(ifstream&);
    void set_id(int);
    void set_location(Cart_Point);
    class Model;


protected:
    Cart_Point location;
    char display_code;
    char state;

private:
    int id_num;
};

#endif
