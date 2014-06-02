#include "Game_Object.h"
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "View.h"
#include <fstream>

Game_Object::Game_Object()
{
    state = 's';
    id_num = 0;
    cout << "Game_Object default constructed." << endl;
}

Game_Object::Game_Object(char in_code)
{
    display_code = in_code;
    cout << "Game_Object constructed" << endl;
}

Game_Object::Game_Object(char in_code, int in_id, Cart_Point in_loc)
{
    display_code = in_code;
    id_num = in_id;
    location = in_loc;
    cout << "Game_Object constructed." << endl;
}

Cart_Point Game_Object::get_location()
{
    return location;
}

int Game_Object::get_id()
{
    return id_num;
}

void Game_Object::show_status()
{
    cout << display_code << id_num << " at " << location;
}

char Game_Object::get_display_code()
{
    return display_code;
}

//draws the game objects display code and id in the designated area on the board
void Game_Object::drawself(char* ptr)
{
    (*ptr) = get_display_code();
    *(ptr + 1) = '0' + get_id();
}

bool Game_Object::is_alive()
{
    return true;
}

void Game_Object::save(ofstream& file)
{
    file << get_display_code() << endl;
    file << get_id() << endl;
    file << get_location().x << endl;
    file << get_location().y << endl;
    file << state << endl;
}

void Game_Object::restore(ifstream& file)
{
    char a;
    file >> a;

    int id;
    file >> id;
    id_num = id;

    double x, y;
    file >> x >> y;
    location.x = x;
    location.y = y;

    char s;
    file >> s;
    state = s;

}

Game_Object::~Game_Object()
{
    cout << "Game_Object destructed." << endl;
}

