#include "Model.h"
#include "Miner.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"
#include "Person.h"
#include "View.h"
#include "Soldier.h"
#include <list>
#include "Inspector.h"
#include <fstream>

using namespace std;

int global_object_counter = 0;
int global_active_counter = 0;
int global_miner_counter = 0;
int global_soldier_counter = 0;
int global_inspector_counter = 0;
int global_hall_counter = 0;
int global_mine_counter = 0;
int global_person_counter = 0;

/* creates the objects on the board, and all of the support objects. */
Model::Model()
{
    time = 0;
    Cart_Point p1(5,1);
    Cart_Point p2(10,1);
    Cart_Point p3(1,20);
    Cart_Point p4(10,20);
    Cart_Point p5(5,15);
    Cart_Point p6(10,15);
    Cart_Point p7(5,5);

    Miner* ptrm1 = new Miner(1,p1);
    object_ptrs.push_front(ptrm1);
    active_ptrs.push_back(ptrm1);
    person_ptr.push_back(ptrm1);
    miner_ptr.push_back(ptrm1);
    global_object_counter += 1;

    Miner* ptrm2 = new Miner(2,p2);
    object_ptrs.push_back(ptrm2);
    active_ptrs.push_back(ptrm2);
    person_ptr.push_back(ptrm2);
    miner_ptr.push_back(ptrm2);
    global_object_counter += 1;

    Gold_Mine* ptrg1 = new Gold_Mine(1,p3);
    object_ptrs.push_back(ptrg1);
    active_ptrs.push_back(ptrg1);
    mine_ptr.push_back(ptrg1);
    global_object_counter += 1;

    Gold_Mine* ptrg2 = new Gold_Mine(2,p4);
    object_ptrs.push_back(ptrg2);
    active_ptrs.push_back(ptrg2);
    mine_ptr.push_back(ptrg2);
    global_object_counter += 1;

    Town_Hall* ptrt1 = new Town_Hall;
    object_ptrs.push_back(ptrt1);
    active_ptrs.push_back(ptrt1);
    hall_ptr.push_back(ptrt1);
    global_object_counter += 1;

    Soldier* ptrs1 = new Soldier(3, p5);
    object_ptrs.push_back(ptrs1);
    active_ptrs.push_back(ptrs1);
    person_ptr.push_back(ptrs1);
    soldier_ptr.push_back(ptrs1);
    global_object_counter += 1;

    Soldier* ptrs2 = new Soldier(4, p6);
    object_ptrs.push_back(ptrs2);
    active_ptrs.push_back(ptrs2);
    person_ptr.push_back(ptrs2);
    soldier_ptr.push_back(ptrs2);
    global_object_counter += 1;

    Inspector* ptri1 = new Inspector(5, p7);
    object_ptrs.push_back(ptri1);
    active_ptrs.push_back(ptri1);
    person_ptr.push_back(ptri1);
    inspect_ptrs.push_back(ptri1);
    global_object_counter += 1;

    cout << "Model default constructed" << endl;
}

Model::~Model()
{
    cout << "Model destructed." << endl;
    for (list<Game_Object*>::iterator it = object_ptrs.begin(); it != object_ptrs.end(); it++)
    {
        delete *it;
    }
}

Person* Model::get_Person_ptr(int id)
{
    list<Person*>::iterator it = person_ptr.begin();
    {
        if (id == 1)
        {
            return *it;
        }
        it++;

        if (id == 2)
        {
            return *(it);
        }
        it++;

        if (id == 3)
        {
            return *(it);
        }
        it++;

        if (id == 4)
        {
            return *(it);
        }
    }
}
Miner* Model::get_Miner_ptr(int id)
{
    list<Miner*>::iterator it = miner_ptr.begin();
    if (id == 1)
    {
        return *(it);
    }
    it++;

    if (id == 2)
    {
        return *(it);
    }
}

Soldier* Model::get_Soldier_ptr(int id)
{
    list<Soldier*>::iterator it = soldier_ptr.begin();

    if (id == 3)
    {
        return *(it);
    }
    it++;

    if (id == 4)
    {
        return *(it);
    }
}

Gold_Mine* Model::get_Gold_Mine_ptr(int id)
{
    list<Gold_Mine*>::iterator it = mine_ptr.begin();
    if (id == 1)
        {
            return *(it);
        }
    it++;
    if (id == 2)
        {
            return *(it);
        }
}

Town_Hall* Model::get_Town_Hall_ptr(int id)
{
    list<Town_Hall*>::iterator it = hall_ptr.begin();
    return (*it);
}

//increments the time and updates each object
bool Model::update()
{
    time += 1;

    for (list<Game_Object*>::iterator it = active_ptrs.begin(); it != active_ptrs.end(); it++)
    {
        (*(*it)).update();
        if ((*(*it)).is_alive() == false)
        {
            it = active_ptrs.erase(it);
            cout << "Dead object removed" << endl;
        }
    }
}

//plots each object on the board and draws the board
void Model::display(View &view)
{
    //cout << "Time: " << time << endl;
    view.clear();
    for (list<Game_Object*>::iterator it = active_ptrs.begin(); it != active_ptrs.end(); it++)
    {
        view.plot(*(it));
    }
    view.draw();
}

//shows the status for each object on the board
void Model::show_status()
{
    cout << "Time: " << time << endl;

    for (list<Game_Object*>::iterator it = object_ptrs.begin(); it != object_ptrs.end(); it++)
    {
        (*(*it)).show_status();
    }
}

void Model::handle_new_command(char type, int in_id, double x, double y)
{
    Cart_Point location(x,y);

    if (type == 'g')
    {
        for (list<Gold_Mine*>::iterator it = mine_ptr.begin(); it != mine_ptr.end(); it++)
        {
            if ((*(*it)).get_id() == in_id)
            {
                cout << "DEBUG invalid id!" << endl;
                //THROW EXCEPTION HERE
            }
        }

        Gold_Mine* ptr = new Gold_Mine(in_id, location);
        object_ptrs.push_back(ptr);
        active_ptrs.push_back(ptr);
        mine_ptr.push_back(ptr);
        global_mine_counter += 1;
        global_object_counter += 1;
    }

    else if (type == 't')
    {
        for (list<Town_Hall*>::iterator it = hall_ptr.begin(); it != hall_ptr.end(); it++)
        {
            if ((*(*it)).get_id() == in_id)
            {
                cout << "DEBUG invalid id!" << endl;
                //THROW EXCEPTION HERE
            }
        }

        Town_Hall* ptr = new Town_Hall(in_id, location);
        object_ptrs.push_back(ptr);
        active_ptrs.push_back(ptr);
        hall_ptr.push_back(ptr);
        global_hall_counter += 1;
        global_object_counter += 1;
    }

    else if (type == 'm')
    {
        for (list<Person*>::iterator it = person_ptr.begin(); it != person_ptr.end(); it++)
        {
            if ((*(*it)).get_id() == in_id)
            {
                cout << "DEBUG invalid id!" << endl;
                //THROW EXCEPTION HERE
            }
        }

        Miner* ptr = new Miner(in_id, location);
        object_ptrs.push_back(ptr);
        active_ptrs.push_back(ptr);
        person_ptr.push_back(ptr);
        miner_ptr.push_back(ptr);
        global_miner_counter += 1;
        global_person_counter += 1;
        global_object_counter += 1;
    }

    else if (type == 's')
    {
        for (list<Person*>::iterator it = person_ptr.begin(); it != person_ptr.end(); it++)
        {
            if ((*(*it)).get_id() == in_id)
            {
                cout << "DEBUG invalid id!" << endl;
                //THROW EXCEPTION HERE
            }
        }

        Soldier* ptr = new Soldier(in_id, location);
        object_ptrs.push_back(ptr);
        active_ptrs.push_back(ptr);
        person_ptr.push_back(ptr);
        soldier_ptr.push_back(ptr);
        global_soldier_counter += 1;
        global_person_counter += 1;
        global_object_counter += 1;
    }

    else if (type == 'i')
    {
        for (list<Person*>::iterator it = person_ptr.begin(); it != person_ptr.end(); it++)
        {
            if ((*(*it)).get_id() == in_id)
            {
                cout << "DEBUG invalid id!" << endl;
                //THROW EXCEPTION HERE
            }
        }

        Inspector* ptr = new Inspector(in_id, location);
        object_ptrs.push_back(ptr);
        active_ptrs.push_back(ptr);
        person_ptr.push_back(ptr);
        inspect_ptrs.push_back(ptr);
        global_inspector_counter += 1;
        global_person_counter += 1;
        global_object_counter += 1;
    }

}

void Model::save(ofstream& file)
{
    file << time << endl;
    file << active_ptrs.size() << endl;
    cout << "model saved" << endl;

    for (list<Game_Object*>::iterator it = active_ptrs.begin(); it != active_ptrs.end(); it++)
    {
        file <<(*(*it)).get_display_code() << endl;
    }
    for (list<Game_Object*>::iterator it = active_ptrs.begin(); it != active_ptrs.end(); it++)
    {
            file << (*(*it)).get_id() << endl;
    }

    for (list<Game_Object*>::iterator it = active_ptrs.begin(); it != active_ptrs.end(); it++)
    {
        (*(*it)).save(file);
    }
}

void Model::restore(ifstream& file)
{

    for (list<Game_Object*>::iterator it = object_ptrs.begin(); it != object_ptrs.end(); it++)
    {
        delete *it;
        //object_ptrs.erase(it);
    }

    list<Inspector*>::iterator it_inspector = inspect_ptrs.begin();
    for (int i = 0; i < inspect_ptrs.size() + global_inspector_counter; i++)
    {
        it_inspector = inspect_ptrs.erase(it_inspector);
    }

    list<Miner*>::iterator it_miner = miner_ptr.begin();
    for (int i = 0; i <= miner_ptr.size() + global_miner_counter; i++)
    {
        it_miner = miner_ptr.erase(it_miner);
    }

    list<Soldier*>::iterator it_soldier = soldier_ptr.begin();
    for (int i = 0; i <= soldier_ptr.size() + global_soldier_counter; i++)
    {
        it_soldier = soldier_ptr.erase(it_soldier);
    }

    list<Gold_Mine*>::iterator it_gold = mine_ptr.begin();
    for (int i = 0; i <= mine_ptr.size() + global_mine_counter; i++)
    {
        it_gold = mine_ptr.erase(it_gold);
    }

    list<Town_Hall*>::iterator it_hall = hall_ptr.begin();
    for (int i = 0; i <= hall_ptr.size() + global_hall_counter; i++)
    {
        it_hall = hall_ptr.erase(it_hall);
    }

    list<Person*>::iterator it_person = person_ptr.begin();
    for (int i = 0; i <= person_ptr.size() + global_person_counter; i++)
    {
        it_person = person_ptr.erase(it_person);
    }

    cout << "active pointer list size before erase is size: " << active_ptrs.size() << endl;
    list<Game_Object*>::iterator it_objects = object_ptrs.begin();
    for (int i = 0; i <= object_ptrs.size() + global_object_counter; i++)
    {
        it_objects = object_ptrs.erase(it_objects);
    }

    list<Game_Object*>::iterator it_active = active_ptrs.begin();
    for (int i = 0; i <= global_object_counter; i++)
    {
        it_active = active_ptrs.erase(it_active);
    }

    cout << "inspector pointers list: " << inspect_ptrs.size() << endl;
    cout << "the size of the miner pointers list is: " << miner_ptr.size() << endl;
    cout << "Soldier pointer list size: " << soldier_ptr.size() << endl;
    cout << "gold miner pointers list: " << mine_ptr.size() << endl;
    cout << "town hall pointers list: " << hall_ptr.size() << endl;
    cout << "the size of the object pointers list is: " << object_ptrs.size() << endl;
    cout << "the size of the active pointers list is: " << active_ptrs.size() << endl;

    int object_ptrs_size;
    file >> time;
    file >> object_ptrs_size;


    char object_array[object_ptrs_size];
    int id_array[object_ptrs_size];
    for (int i = 0; i < object_ptrs_size; i++)
    {
            file >> object_array[i];
    }

    for (int i = 0; i < object_ptrs_size; i++)
    {
        file >> id_array[i];
    }


    for (int i = 0; i < object_ptrs_size; i++)
    {
        cout << object_array[i] << endl;
        cout << id_array[i] << endl;
    }

    Cart_Point x;
    for (int i = 0; i < object_ptrs_size; i++)
    {
        if (object_array[i] == 'M' || object_array[i] == 'm')
        {
            Miner* ptr = new Miner(id_array[i], x);
            object_ptrs.push_back(ptr);
            active_ptrs.push_back(ptr);
            person_ptr.push_back(ptr);
            miner_ptr.push_back(ptr);
        }

        if (object_array[i] == 'G' || object_array[i] == 'g')
        {
            Gold_Mine* ptr = new Gold_Mine(id_array[i], x);
            object_ptrs.push_back(ptr);
            active_ptrs.push_back(ptr);
            mine_ptr.push_back(ptr);
        }

        if (object_array[i] == 't' || object_array[i] == 'T')
        {
            Town_Hall* ptr = new Town_Hall(id_array[i], x);
            object_ptrs.push_back(ptr);
            active_ptrs.push_back(ptr);
            hall_ptr.push_back(ptr);
        }

        if (object_array[i] == 's' || object_array[i] == 'S')
        {
            Soldier* ptr = new Soldier(id_array[i], x);
            object_ptrs.push_back(ptr);
            active_ptrs.push_back(ptr);
            person_ptr.push_back(ptr);
            soldier_ptr.push_back(ptr);
        }

        if (object_array[i] == 'i' || object_array[i] == 'I')
        {
            Inspector* ptr = new Inspector(id_array[i], x);
            object_ptrs.push_back(ptr);
            active_ptrs.push_back(ptr);
            person_ptr.push_back(ptr);
            inspect_ptrs.push_back(ptr);
        }
    }
    cout << "after restore, active pointers list is now size: " << active_ptrs.size() << endl;

    list<Miner*>::iterator it_miners = miner_ptr.begin();
    list<Soldier*>::iterator it_soldiers = soldier_ptr.begin();
    list<Inspector*>::iterator it_inspectors = inspect_ptrs.begin();
    list<Gold_Mine*>::iterator it_mines = mine_ptr.begin();
    list<Town_Hall*>::iterator it_halls = hall_ptr.begin();
    for (int i = 0; i < object_ptrs_size; i++)
    {
        if (object_array[i] == 'M' || object_array[i] =='m')
        {
            (*(*it_miners)).restore(file);
            if (it_miners != miner_ptr.end())
            {
                it_miners++;
            }
        }

        if (object_array[i] == 'S' || object_array[i] == 's')
        {
            (*(*it_soldiers)).restore(file);
            if (it_soldiers != soldier_ptr.end())
            {
                it_soldiers++;
            }
        }

        if (object_array[i] == 'I' || object_array[i] == 'i')
        {
            (*(*it_inspectors)).restore(file);
            it_inspectors++;
        }

        if (object_array[i] == 'G' || object_array[i] == 'g')
        {
            (*(*it_mines)).restore(file);
            it_mines++;
        }

        if (object_array[i] == 'T' || object_array[i] == 't')
        {
            (*(*it_halls)).restore(file);
            it_halls++;
        }

    }
}
