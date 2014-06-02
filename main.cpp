#include <iostream>
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Game_Object.h"
#include "Person.h"
#include "Miner.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"
#include "View.h"
#include "Model.h"
#include "Game_Command.h"
#include "Soldier.h"
#include <list>
#include "Input_Handling.h"
#include "Inspector.h"

using namespace std;

int main()
{
    char command;

    Model model;
    View board;
    cout << endl;
    model.show_status();
    model.display(board);

    //consists of a switch statement and a list of commands.  Each command will call a function in the game_commands and will update the game board and
    //show the status of each game object
    while (command != 'q')
    {
        cout << "Enter command: ";
        cin >> command;
        try
        {
            if (command ==('m', 'w', 's', 'g', 'r', 'l', 'a', 'q'))
            {
                throw Invalid_Input("DEBUG not a valid command");
            }
        switch (command)
        {
            case 'm':
            {
                do_move_command(model);
                model.display(board);
                break;
            }

            case 'w':
            {
                do_start_mining_command(model);
                model.display(board);
                break;
            }

            case 's':
            {
                do_stop_command(model);
                model.display(board);
                break;
            }

            case 'g':
            {
                do_go_command(model);
                model.display(board);
                break;
            }

            case 'r':
            {
                do_run_command(model);
                model.show_status();
                model.display(board);
                break;
            }

            case 'l':
            {
                do_status_command(model);
                break;
            }

            case 'a':
            {
                do_attack_command(model);
                model.display(board);
                break;
            }

            case 'n':
            {
                do_create_object_command(model);
                model.display(board);
                break;
            }

            case 'i':
            {
                do_inspect_command(model);
                break;
            }

            case 'S':
                {
                    do_save_command(model);
                    break;
                }

            case 'R':
                {
                    do_restore_command(model);
                    model.display(board);
                    break;
                }

            case 'q':
            {
                do_quit_command(model);
                return 0;
            }

            //default: cout << "ERROR: Please enter a valid command!" << endl << endl;
        }
        }
        catch (Invalid_Input& except)
        {
            cout << "Invalid input - " << except.msg_ptr << endl;
            break;
        }

    }
return 0;
}



