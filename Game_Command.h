#ifndef GAME_COMMAND
#define GAME_COMMAND

#include "Model.h"

void do_move_command(Model&);
void do_start_mining_command(Model&);
void do_stop_command(Model&);
void do_go_command(Model&);
void do_run_command(Model&);
void do_quit_command(Model&);
void do_status_command(Model&);
void do_attack_command(Model&);
void do_create_object_command(Model&);
void do_inspect_command(Model&);
void do_save_command(Model&);
void do_restore_command(Model&);

#endif // GAME_COMMAND
