#include "Soldier.h"
#include "Model.h"
#include <math.h>
#include "Person.h"
#include "Cart_Point.h"
#include <fstream>

Model smodel;

Soldier::Soldier(): Person('S')
{
    state = 's';
    attack_strength = 2;
    range = 2.0;
    target = NULL;
    cout << "Soldier default constructed." << endl;
}

Soldier::Soldier(int in_id, Cart_Point in_loc): Person('S', in_id, in_loc)
{
    state = 's';
    attack_strength = 2;
    range = 2.0;
    target = NULL;
    cout << "Soldier constructed." << endl;
}

void Soldier::start_attack(Person* in_target)
{
    if (is_alive() == true)
    {
        Cart_Point a, b;
        a = (*in_target).get_location();
        b = get_location();
        if (cart_distance(a, b) <= range)
        {
            target = in_target;
            state = 'a';
            cout << "Attacking." << endl;
        }
        else if (cart_distance((*in_target).get_location(), get_location()) > range)
        {
            cout << "Target is out of range." << endl;
        }
    }

    else
        cout << "I am dead.  You do not have the ability to summon the undead." << endl;
}

bool Soldier::update()
{
    if (state == 'm')
    {
        if (update_location() == true)
        {
            state = 's';
            return true;
        }

        else
        {
            return false;
        }
    }

    else if (state == 'x')
    {
        return false;
    }

    else if (state == 's')
    {
        return false;
    }

    else if (state == 'a')
    {
        if (cart_distance((*target).get_location(), get_location()) > range)
        {
            cout << "Target is out of range." << endl;
            state = 's';
            return true;
        }

        if (cart_distance((*target).get_location(), get_location()) <= range)
        {
            if ((*target).is_alive() == true)
            {
                cout << "Take that!" << endl;
                (*target).take_hit(attack_strength, this);
                state = 'a';
                return false;
            }

            else if ((*target).is_alive() == false)
            {
                cout << "I win." << endl;
                state = 's';
                return true;
            }
        }

    }
    else
    {
        return false;
    }
}

void Soldier::show_status()
{
    cout << "Soldier status: ";
    Person::show_status();

    if (state == 'a')
        cout << " Attacking" << endl;
}

bool Soldier::update_location()
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

int Soldier::get_attack_strength()
{
    return attack_strength;
}

void Soldier::save(ofstream& file)
{
    Person::save(file);

    file << attack_strength << endl;
    file << range << endl;

    if (target == NULL)
    {
        file << -1 << endl;
    }

    else
    {
        file << (*target).get_id();
    }

    cout << "Soldier saved!" << endl;
}

void Soldier::restore(ifstream& file)
{
    Person::restore(file);

    int a;
    double b;
    file >> a;
    attack_strength = a;
    file >> b;
    range = b;

    int c;
    file >> c;
    if (c == -1)
    {
        target = NULL;
    }

    else
    {
        target = smodel.get_Person_ptr(c);
    }
    show_status();
}

void Soldier::take_hit(int attack_strength, Person* attacker_ptr)
{
    Person::take_hit(attack_strength, attacker_ptr);
    start_attack(attacker_ptr);
}


Soldier::~Soldier()
{
    cout << "Soldier destructed." << endl;
}


