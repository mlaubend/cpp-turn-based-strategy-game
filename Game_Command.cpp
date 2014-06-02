#include "Game_Command.h"
#include "Model.h"
#include "View.h"
#include <list>
#include "Inspector.h"
#include <string>
#include <fstream>

using namespace std;

/*called when the user inputs 'm' as a command.  Moves the object to the designated point.*/
void do_move_command(Model& model)
{
    int ID, a, b;
    cin >> ID >> a >> b;
    Cart_Point x(a,b);

    for (list<Person*>::iterator it = model.person_ptr.begin(); it != model.person_ptr.end(); it++)
    {
        if ((*(*it)).get_id() == ID)
        {
            (*(*it)).start_moving(x);
        }
    }
}

/*called when the user inputs the 'w' command.  Three variables are inputted and the designated miner is set to mine and deposit at the
designated gold mine and towh hall*/
void do_start_mining_command(Model& model)
{
    int ID1, ID2, ID3;
    cin >> ID1 >> ID2 >> ID3;
    for (list<Miner*>::iterator it_miner = model.miner_ptr.begin(); it_miner != model.miner_ptr.end(); it_miner++)
    {
        if ((*(*it_miner)).get_id() != ID1)
        {
            continue;
        }
        else
        {
            cout << "got the miner" << endl;
            for (list<Gold_Mine*>::iterator it_mine = model.mine_ptr.begin(); it_mine != model.mine_ptr.end(); it_mine++)
            {
                if ((*(*it_mine)).get_id() != ID2)
                {
                    continue;
                }
                else
                {
                    cout << "got the gold mine" << endl;
                    for (list<Town_Hall*>::iterator it_hall = model.hall_ptr.begin(); it_hall != model.hall_ptr.end(); it_hall++)
                    {
                        if ((*(*it_hall)).get_id() == ID3)
                        {
                            //continue;
                            cout << "got the town hall" << endl;
                            (*(*it_miner)).start_mining((*it_mine), (*it_hall));
                        }
                    }
                }
            }
        }
    }
}

/*called when the user inputs the 's' command. It stops the designated object where it is.*/
void do_stop_command(Model& model)
{
    int ID4;
    cin >> ID4;

    for (list<Person*>::iterator it = model.person_ptr.begin(); it != model.person_ptr.end(); it++)
    {
        if ((*(*it)).get_id() == ID4)
        {
            (*(*it)).stop();
        }
    }
}

/*called when the user inputs the 'g' command.  It updates the board and increments the time by 1*/
void do_go_command(Model& model)
{
    cout << "Advancing one tick." << endl;
    model.update();
}

/*called when the user inputs the 'r' command.  It updates the board and increments the time until it reaches 5 or the next event*/
void do_run_command(Model& model)
{
    cout << "Advancing to next event." << endl;
    for (int i = 0; i < 5; i++)
    {
        //model.update();
        if (model.update() == true)
            break;
    }
}

//called when user inputs the 'l' command.  outputs the status of all current objects
void do_status_command(Model& model)
{

    model.show_status();
}

//called when the user inputs the 'a' command.  It sets to attack the first object with the second object.
void do_attack_command(Model& model)
{
    int ID1, ID2;
    cin >> ID1 >> ID2;

    for (list<Person*>::iterator it = model.person_ptr.begin(); it != model.person_ptr.end(); it++)
    {
        if ((*(*it)).get_id() != ID1)
        {
            continue;
        }
        else
        {
            for (list<Person*>::iterator it2 = model.person_ptr.begin(); it2 != model.person_ptr.end(); it2++)
            {
                if ((*(*it2)).get_id() != ID2)
                {
                    continue;
                }
                else
                {
                    (*(*it)).start_attack(*it2);
                }
            }
        }
    }
}

//called when the user inputs the 'n' command.  It creates a game object during run-time
void do_create_object_command(Model& model)
{
    char type;
    int in_id;
    double x, y;
    cin >> type >> in_id >> x >> y;
    model.handle_new_command(type, in_id, x, y);
}


//called when the user inputs the 'i' command.  Commands the inspector to start inspecting at  
void do_inspect_command(Model& model)
{
    int ID1;
    cin >> ID1;

    list<Gold_Mine*>::iterator it = model.mine_ptr.begin();
    list<Gold_Mine*>::iterator its = model.mine_ptr.begin();
    its++;
    list<Person*>::iterator person_it = model.person_ptr.begin();
    advance(person_it, 4);
    (*(*person_it)).set_destination((*(*model.mine_ptr.begin())).get_location());

    Gold_Mine* first;
    first = (*its);
    Gold_Mine* second;

    if (cart_distance((*(*person_it)).get_location(), (*(*it)).get_location()) > cart_distance((*(*person_it)).get_location(), (*(*its)).get_location()))
    {
        first = (*its);
        second = (*it);
    }

    else
    {
        first = (*it);
        second = (*its);
    }

    list<Gold_Mine*>::iterator it_begin = model.inspector_ptrs.begin();
    list<Inspector*>::iterator it_inspect = model.inspect_ptrs.begin();
    (*(*it_inspect)).mine = (first);
    it_begin++;
    (*(*it_inspect)).mine2 = (second);
    (*(*it_inspect)).origin = (*(*it_inspect)).get_location();

    (*(*it_inspect)).start_inspecting();
}

void do_save_command(Model& model)
{
    string filename;
    cin >> filename;
    ofstream output(filename.c_str());
    cout << "saving game!" << endl;
    model.save(output);
    output.close();
}

void do_restore_command (Model& model)
{
    string filename;
    cin >> filename;
    ifstream input(filename.c_str());
    cout << "restoring game!" << endl;
    model.restore(input);
    input.close();
}

//called when the user inputs the 'q' command
void do_quit_command(Model& model)
{
    cout << "Terminating program" << endl;
}
