#include "Person.h"
#include "Game_Object.h"
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Gold_Mine.h"
#include <fstream>

Person::Person()
{
    speed = 5;
    health = 5;
    cout << "Person default constructed." << endl;
}

Person::Person(char in_code): Game_Object(in_code)
{
    speed = 5;
    health = 5;
    cout << "Person constructed." << endl;
}

Person::Person(char in_code, int in_id, Cart_Point in_loc): Game_Object(in_code, in_id, in_loc)
{
    speed = 5;
    health = 5;
    cout << "Person constructed." << endl;
}

void Person::start_moving(Cart_Point d)
{

    if (is_alive() == true)
    {
        destination = d;
        setup_destination(destination);
        state = 'm';
        cout << "Moving " << get_id() << " to " << destination << endl;
        cout << display_code <<get_id() << ": On my way." << endl;
    }
    else
        cout << "I am dead.  I may move but you just cannot see me" << endl;
}

void Person::setup_destination(Cart_Point dest)
{
delta = ((destination - location) * (speed / cart_distance(destination, location)));
}

Cart_Point Person::get_destination()
{
    return destination;
}

void Person::set_destination(Cart_Point dest)
{
    destination = dest;
}

void Person::stop()
{
    state = 's';
    cout << "Stopping " << get_id() << endl;
    cout << display_code << get_id() << " : All right." << endl;
}

void Person::show_status()
{
    Game_Object::show_status();

    if (state == 's')
    {
        cout << " Moving at speed of " << speed << " towards " << destination;
        cout << " at each step of " << delta << endl;
        cout << " Stopped. " << health << endl;
    }
	if (state == 'm')
    {
        cout << " Moving at speed of " << speed << " towards " << destination;
        cout << " at each step of  " << delta << endl;
    }

    if (state == 'x')
    {
        cout << " Moving at speed of " << speed << " towards " << destination;
        cout << " at each step of  " << delta;
        cout << " is dead" << endl;
    }
}

Cart_Vector Person::get_delta()
{
    return delta;
}

Person::~Person()
{
    cout << "Person destructed." << endl;
}

void Person::start_mining()
{
    cout << "Sorry, I can't work a mine." << endl;
}

bool Person::is_alive()
{
    if (state == 'x')
    {
        return false;
    }

    else
    {
        return true;
    }
}

void Person::take_hit(int attack_strength, Person* attacker_ptr)
{
    health -= attack_strength;

    if (health < 3)
    {
        if (display_code == 'M')
        {
            display_code = 'm';
        }
        if (display_code == 'I')
        {
            display_code = 'i';
        }
        if (display_code == 'S')
        {
            display_code = 's';
        }
    }

    if (health <= 0)
    {
        cout << "Ahhhh, I am dying." << endl;
        state = 'x';
    }
    else
        cout << "Ouch!" << endl;
}

void Person::start_attack(Person*)
{
    cout << "I can't attack." << endl;
}

double Person::get_speed()
{
    return speed;
}
int Person::get_health()
{
    return health;
}

void Person::save(ofstream& file)
{
    Game_Object::save(file);
    file << get_health() << endl;
    file << get_destination().x << endl;
    file << get_destination().y << endl;
    file << get_delta().x << endl;
    file << get_delta().y << endl;
}

void Person::restore(ifstream& file)
{
    Game_Object::restore(file);

    int a;
    file >> a;
    health = a;

    double x, y;
    file >> x >> y;
    destination.x = x;
    destination.y = y;

    double w, z;
    file >> w >> z;
    delta.x = w;
    delta.y = z;
}

