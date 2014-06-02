#include "Town_Hall.h"
#include "Cart_Point.h"
#include "Game_Object.h"
#include <fstream>

//initializes the Town_Hall variables to their default values
Town_Hall::Town_Hall():Game_Object('t')
{
    state = 'o';
    amount = 0;
    cout << "Town_Hall default constructed" << endl;
}

//overwrites the default values with their respective new input values.  If a new input value was not specified, it reverts to the default.
Town_Hall::Town_Hall(int in_id, Cart_Point in_loc):Game_Object('t', in_id, in_loc)
{
    state = 'o';
    amount = 0;
    cout << "Town_Hall constructed" << endl;
}

//return the location.
Cart_Point Town_Hall::get_location()
{
    return location;
}

//deposits the specified amount of gold into the Town Hall
void Town_Hall::deposit_gold(double deposit_amount)
{
    amount += deposit_amount;
    update();
}

//checks to see if the town hall has more than 50 gold.  If it does, the Town Hall's state and display code are changed and an "upgrade" message is printed
bool Town_Hall::update()
{
    if (amount >= 50 && state != 'u')
    {
        state ='u';
        display_code = 'T';
        cout << display_code << get_id() << " has been upgraded"<< endl;
        return true;
    }
    else
        return false;
}

//shows Town Hall variables and their respective values
void Town_Hall::show_status()
{
    cout << "Town_Hall status: ";
    Game_Object::show_status();
    cout << " Contains " << amount << " of gold.";
    if (state == 'o')
        cout << " Not yet upgraded" << endl;
    else
        cout << " Upgraded" << endl;
}

double Town_Hall::get_amount()
{
    return amount;
}

void Town_Hall::save(ofstream& file)
{
    Game_Object::save(file);
    file << get_amount() << endl;

    cout << "Town_Hall saved!" << endl;
}

void Town_Hall::restore(ifstream& file)
{
    Game_Object::restore(file);
    double a;
    file >> a;
    amount = a;
    show_status();
}

Town_Hall::~Town_Hall()
{
    cout << "Town_Hall destructed." << endl;
}

