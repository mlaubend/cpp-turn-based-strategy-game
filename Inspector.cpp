#include "Inspector.h"
#include <iostream>
#include "Model.h"
#include "Cart_Point.h"
#include "Person.h"
#include <math.h>
#include <fstream>

using namespace std;

Model imodel;

//have the inspector use the mine list, and increment once complete
Inspector::Inspector(): Person('I')
{
    state = 's';
	mine = NULL;
	mine2 = NULL;
	origin = location;
	gold1 = 0;
	gold2 = 0;
	cout << "Inspector default constructed" << endl;
}

Inspector::Inspector(int in_id, Cart_Point in_loc): Person('I', in_id, in_loc)
{
    state = 's';
	mine = NULL;
	mine2 = NULL;
	origin = location;
	gold1 = 0;
	gold2 = 0;
	cout << "Inspector constructed" << endl;
}


bool Inspector::update_location()
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

Inspector::~Inspector()
{
    cout << "Inspector destructed" << endl;
}

void Inspector::show_status()
{
    cout << "Inspector status: ";
    Person::show_status();

    if (state == 'o')
    {
        cout << " Outbound to a mine" << endl;
    }

    else if (state == 'i')
    {
        cout << " Inbound to a mine" << endl;
    }
}

bool Inspector::update()
{
    //calls the update_location function and tests if the inspector has arrived at the location.  if it has, the state is changed to 's'.
    if (state == 'm')
    {
        if (update_location() == true)
        {
            state = 's';
            return true;
        }
    }
    /*calls the update_location function and tests if the Inspector has arrived at the location.  If it has, the state is changed to 'i'
    and the Inspector begins to inspect the next time tick*/
    else if (state == 'o')
    {
        if (update_location() == true)
        {
            if (gold1 == 0)
            {
                cout << "this mine contains " << (*mine).get_amount() << " of gold" << endl;
                gold1 = (*mine).get_amount();
                cout << gold1 << endl;
                set_destination((*mine2).get_location());
                setup_destination(get_destination());
                state = 'o';
                return true;
            }

            else
            {
                cout << "this mine contains " << (*mine2).get_amount() << " of gold" << endl;
                cout << "starting back" << endl;
                gold2 = (*mine2).get_amount();
                set_destination((*mine).get_location());
                setup_destination(get_destination());
                state = 'i';
            }
        }
    }

    else if (state == 'i')
    {
        if (update_location() == true)
        {
            if (gold1 != 0)
            {
                gold1 -= (*mine).get_amount();
                cout << "Amount of gold removed from this mine is " << gold1 << " gold since the last time I've been here" << endl;
                gold1 = 0;
                set_destination((*mine2).get_location());
                setup_destination(get_destination());
                state = 'i';
                return true;
            }

            else if (gold2 != 0)
            {
                gold2 -= (*mine2).get_amount();
                cout << "this mine has lost " << gold2 << " gold since the last time I've been here" << endl;
                gold2 = 0;
                mine = NULL;
                mine2 = NULL;
                set_destination(origin);
                setup_destination(get_destination());
                state = 'i';
                return true;
            }

            else
            {
                state = 's';
                cout << "Inspection trip completed" << endl;
            }
        }
    }
}

void Inspector:: start_inspecting()
{
    cout << "starting inspection trip" << endl;
    set_destination((*mine).get_location());
    setup_destination(get_destination());
    state = 'o';
}

void Inspector::save(ofstream& file)
{
    Person::save(file);
    file << gold1 << endl;
    file << gold2 << endl;
    file << origin.x << endl;
    file << origin.y << endl;

    if (mine == NULL)
    {
        file << -1 << endl;
    }
    else
    {
        file << (*mine).get_id() << endl;
    }

    if (mine2 == NULL)
    {
        file << -1 << endl;
    }
    else
    {
        file << (*mine2).get_id() << endl;
    }


    cout << "Inspector saved!" << endl;
}

void Inspector::restore(ifstream& file)
{
    Person::restore(file);
    double a, b, e, f;
    file >> a >> b;
    gold1 = a;
    gold2 = b;
    origin.x = e;
    origin.y = f;

    int c, d;
    file >> c >> d;
    if (c == -1)
    {
        mine = NULL;
    }

    else
    {
        mine = imodel.get_Gold_Mine_ptr(c);
    }

    if (d == -1)
    {
        mine2 = NULL;
    }

    else
    {
        mine2 = imodel.get_Gold_Mine_ptr(d);
    }

    show_status();
}

void Inspector::take_hit(int attacker_strength, Person* attacker_ptr)
{
    Person::take_hit(attacker_strength, attacker_ptr);
    Cart_Point flee;
    flee.x = location.x + 1.5 * (location.x - (*attacker_ptr).get_location().x);
    flee.y = location.y + 1.5 * (location.y - (*attacker_ptr).get_location().y);
    start_moving(flee);
}

