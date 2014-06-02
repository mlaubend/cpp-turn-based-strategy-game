#include <iostream>
#include "Gold_Mine.h"
#include "Cart_Point.h"
#include <fstream>
using namespace std;

//initializes Gold_Mine variables to their default values
Gold_Mine::Gold_Mine():Game_Object('G')
{
    state = 'f';
    amount = 100;
    cout << "Gold_mine default constructed" << endl;
}

//overwrites the Gold_Mine default values with the new input values
Gold_Mine::Gold_Mine(int in_id, Cart_Point in_loc):Game_Object('G', in_id, in_loc)
{
    state = 'f';
    amount = 100;
    cout << "Gold_Mine constructed" << endl;
}

//it's SUPPOSED to return the location, but it's not working right now.
Cart_Point Gold_Mine::get_location()
{
    return location;
}

//also SUPPOSED to return the id number.  It's also not working at the moment.
/*int Gold_Mine::get_id()
{
    return id_num;
}*/

//function that returns true is the gold mine is empty
bool Gold_Mine::is_empty()
{
    if (amount == 0)
    {
        update();
        return true;
    }
    else
        return false;
}

//reduces the amount of gold in the gold mine by the specified amount
double Gold_Mine::dig_gold(double amount_to_dig = 35.0)
{
    if (amount >= amount_to_dig)
    {
        amount -= amount_to_dig;
        is_empty();
        return amount_to_dig;
    }
    else
    {
        double a = amount;
        amount = 0;
        is_empty();
        return a;
    }
}

//checks if the gold mine is empty.  If it is empty, it will print a message
bool Gold_Mine::update()
{
    if (amount == 0 && state != 'e')
    {
        state = 'e';
        display_code = 'g';
        cout << "Gold_Mine " << get_id() << " has been depleted" << endl;
        return true;
    }
    else
        return false;
}

//prints out the variables and respective values of the Gold Mine
void Gold_Mine::show_status()
{
    cout << "Gold_Mine Status: ";
    Game_Object::show_status();
    cout << " Contains " << amount << endl;
}

Gold_Mine::~Gold_Mine()
{
    cout << "Gold_Mine destructed." << endl;
}

double Gold_Mine::get_amount()
{
    return amount;
}

void Gold_Mine::save(ofstream& file)
{
    Game_Object::save(file);
    file << get_amount() << endl;
    cout << "Gold_Mine saved!" << endl;
}

void Gold_Mine::restore(ifstream& file)
{
    Game_Object::restore(file);
    double a;
    file >> a;
    amount = a;
    show_status();
}
