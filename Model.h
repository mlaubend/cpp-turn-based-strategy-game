#ifndef MODEL
#define MODEL

#include "Game_Object.h"
#include "Person.h"
#include "View.h"
#include "Miner.h"
#include "Soldier.h"
#include <list>
#include "Inspector.h"

class Model
{
public:
    Model();
    ~Model();
    int get_time();
    Person* get_Person_ptr(int);
    Gold_Mine* get_Gold_Mine_ptr(int);
    Town_Hall* get_Town_Hall_ptr(int);
    Miner* get_Miner_ptr(int);
    Soldier* get_Soldier_ptr(int);
    bool update();
    void display(View&);
    void show_status();
    void handle_new_command(char, int, double, double);
    void get_gold_mine();
    void save(ofstream&);
    void restore(ifstream&);

    list<Game_Object*> object_ptrs;
    list<Game_Object*> active_ptrs;
    list<Person*> person_ptr;
    list<Gold_Mine*> mine_ptr;
    list<Town_Hall*> hall_ptr;
    list<Miner*> miner_ptr;
    list<Soldier*> soldier_ptr;
    list<Inspector*> inspect_ptrs;
    list<Gold_Mine*> inspector_ptrs;

private:
    int time;
};
#endif // MODEL
