#ifndef INSPECTOR_H
#define INSPECTOR_H

#include "Person.h"
#include "Gold_Mine.h"
#include <list>
//#include "Model.h"

class Model;

class Inspector: public Person
{
public:
    Inspector();
    ~Inspector();
    Inspector(int, Cart_Point);
    bool update();
    bool update_location();
    void show_status();
    void start_inspecting();
    Cart_Point origin;
    void save(ofstream&);
    void restore(ifstream&);
    double get_gold1();
    double get_gold2();
    void take_hit(int, Person*);

    double gold1;
    double gold2;

    Gold_Mine* mine;
    Gold_Mine* mine2;
};

#endif // INSPECTOR_H
