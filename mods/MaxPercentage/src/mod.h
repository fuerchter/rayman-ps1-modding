#ifndef MOD_H
#define MOD_H

#include <export.h>

#define TXT_X_OFF 24
#define TXT_Y_OFF (16 - 3) // 16 for its height and 3 for empty space on top
#define TXT_COLOR_NORMAL 0
#define TXT_COLOR_COMPLETE 7

void finish_bonus_level(int world, int level);
void on_new_game();
void on_load_level();
void on_level_loop();
void display_hud_level();
void display_hud_total();
void display_obj(Obj *obj);

#endif
