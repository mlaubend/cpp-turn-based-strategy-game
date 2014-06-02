#include <iostream>
#include "Miner.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"
#include "Game_Object.h"
#include "Model.h"
#include <math.h>
#include <fstream>
using namespace std;

Model mmodel;

Miner::Miner(): Person('M')
{
	state = 's';
	amount = 0;
	mine = NULL;
	home = NULL;
	cout << "Miner default constructed" << endl;
}

Miner::Miner(int in_id, Cart_Point in_loc): Person('M', in_id, in_loc)
{
    state = 's';
    amount = 0;
    mine = NULL;
	home = NULL;
	cout << "Miner constructed" << endl;
}

bool Miner::update()
{
    //calls the update_location function and tests if the miner has arrived at the location.  if it has, the state is changed to 's'.
    if (state == 'm')
    {
        if (update_location() == true)
        {
            state = 's';
            return true;
        }
    }
    /*calls the update_location function and tests if the miner has arrived at the location.  If it has, the state is changed to 'g'
    and the miner begins to mine the next time tick*/
    else if (state == 'o')
    {
        if (update_location() == true)
        {
            state = 'g';
            return true;
        }
    }
    /*calls the dig_gold function of the mine, subtracts the specified amount from the mine and adds it to the miner's personal amount.
    the destination is then changed to the home town_hall and the state is finally changed to 'i'.*/
    else if (state == 'g')
    {
        amount += (*mine).dig_gold(35.0);
        cout << display_code << get_id() << ": Got "
        << amount << " gold." << endl;
        set_destination((*home).get_location());
        setup_destination(get_destination());
        state = 'i';
        return true;
    }
    /*tests to see if the miner has reached the home Town_Hall, and if it has the state is changed to 'd'*/
    else if (state == 'i')
    {
        if (update_location() == true)
        {
            state = 'd';
            return true;
        }
    }
    /*deposits the amount of gold carrying into the Town_Hall.  it then checks to see if the mine is empty.  If it is, the state is
    changed to 's' and the user is prompted with a "more work?" question.  if it is not empty, the destination is changed back to the
    mine location and the miner returns for more gold.  The state is changed to 'o'*/
    else if (state == 'd')
    {
        cout << display_code << get_id() << ": Deposit "
        << amount << " of gold." << endl;
        (*home).deposit_gold(amount);
        amount = 0;
        if ((*mine).is_empty() == true)
        {
            state = 's';
            cout << display_code << get_id() << ": More work?" << endl;
            return true;
        }
        else
        {
            set_destination((*mine).get_location());
            setup_destination(get_destination());
            cout << display_code << get_id() << ": Going back for more" << endl;
            state = 'o';
            return true;
        }
    }
    else if (state == 'x')
    {
        state = 'x';
        return false;
    }
    else
        return false;
}

//updates the location of the miner.  If the destination is within one step of the miner, it will return true.
bool Miner::update_location()
{
    Cart_Vector vect;
    vect = (get_destination() - location);
    if (fabs(vect.x) <= fabs((get_delta()).x) && fabs(vect.y) <= fabs((get_delta()).y))
    {
        location = get_destination();
        cout << display_code << get_id() << ": I'm there!" << endl;
        return true;
    }
    else
        location.x = location.x + ((get_delta()).x);
        location.y = location.y + ((get_delta()).y);
        cout << display_code << get_id() << ": step..." << endl;
        return false;
}

//starts the miner to mine.
void Miner::start_mining(Gold_Mine* inputMine, Town_Hall* inputHome)
{
    if (is_alive() == true)
    {
        mine = inputMine;
        home = inputHome;
        set_destination((*mine).get_location());

        setup_destination(get_destination());
        state = 'o';
        cout << "Miner " << get_id() << " mining at Gold_Mine " << (*mine).get_id()
        << " and depositing at Town_Hall " << (*home).get_id() << endl;
        cout << display_code << get_id() << ": Yes, my lord." << endl;
    }
    else
        cout << "I am dead.  Are you kidding me?  Ask a zombie to work!?!?" << endl;
}


void Miner::show_status()
{
    cout << "Miner status: ";
    Person::show_status();

    if (state == 'o')
    {
        cout << " Outbound to a mine" << endl;
    }
    else if (state == 'g')
    {
        cout << " Getting gold from mine." << endl;
    }
    else if (state == 'i')
    {
        cout << " Inbound to home with load: " << get_amount() << endl;
    }
    else if (state == 'd')
        cout << " Depositing gold." << endl;
}

double Miner::get_amount()
{
    return amount;
}

void Miner::save(ofstream& file)
{
    Person::save(file);
    file << amount << endl;

    if (mine == NULL)
    {
        file << -1 << endl;
    }
    else
    {
        file << (*mine).get_id() << endl;
    }

    if (home == NULL)
    {
        file << -1 << endl;
    }
    else
    {
        file << (*mine).get_id() << endl;
    }


    cout << "Miner saved!" << endl;
}

void Miner::restore(ifstream& file)
{
    Person::restore(file);

    double a;
    file >> a;
    amount = a;

    int b;
    file >> b;

    if (b == -1)
    {
        mine = NULL;
    }

    else
    {
        mine = mmodel.get_Gold_Mine_ptr(b);
    }

    int c;
    file >> c;

    if (c == -1)
    {
        home = NULL;
    }
    else
    {
        home = mmodel.get_Town_Hall_ptr(b);
    }
    show_status();
}

void Miner::take_hit(int attacker_strength, Person* attacker_ptr)
{
    Person::take_hit(attacker_strength, attacker_ptr);
    Cart_Point flee;
    flee.x = location.x + 1.5 * (location.x - (*attacker_ptr).get_location().x);
    flee.y = location.y + 1.5 * (location.y - (*attacker_ptr).get_location().y);
    start_moving(flee);
}

Miner::~Miner()
{
    cout << "Miner destructed." << endl;
}
