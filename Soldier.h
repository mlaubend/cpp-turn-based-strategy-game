#ifndef SOLDIER
#define SOLDIER

#include "Person.h"

class Soldier: public Person
{

public:
    Soldier();
    ~Soldier();
    Soldier(int, Cart_Point);
    void start_attack(Person*);
    bool update();
    void show_status();
    bool update_location();
    void save(ofstream&);
    void restore(ifstream&);
    int get_attack_strength();
    double get_range();
    void take_hit(int, Person*);

private:
    int attack_strength;
    double range;
    Person* target;

};



#endif // SOLDIER
