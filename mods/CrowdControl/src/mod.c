#include <export.h>
#include "mod.h"
#include "globals.h"

#define DARK_RAY_ADDR 0x801e553c

void CC_LEVEL()
{
    CC_Dark_RAY();
}

void CC_Dark_RAY()
{
    Obj* blackRay;
    Obj* blackFist;
    int isEnabled;

    isEnabled = *(int *)DARK_RAY_ADDR;
    
    // If the effect is disabled and we don't have a Dark Rayman then we do nothing
    if (!isEnabled && black_ray_obj_id == -1)
        return;

    // Create Dark Rayman if it doesn't exist
    if (black_ray_obj_id == -1)
    {
        // Rayman's feet are unused in every level, so convert to Dark Rayman
        blackRay = findfirstObject(TYPE_PIEDS_RAYMAN);
        black_ray_obj_id = blackRay->id;
        
        // Set fields
        memcpy(blackRay, &raytmp, 24);
        blackRay->offset_bx = 80;
        blackRay->offset_by = 80;
        blackRay->offset_hy = 20;
        blackRay->hit_points = 0;
        blackRay->hit_sprite = 254;
        set_main_and_sub_etat(blackRay, 0, 0);
        blackRay->type = TYPE_BLACK_RAY;
        first_obj_init(blackRay);
        obj_init(blackRay);

        // Use one of the nova effect objects for Dark Rayman's fist
        blackFist = findfirstObject(TYPE_NOVA2);
        black_fist_obj_id = blackFist->id;

        // Set fields
        memcpy(blackFist, &level.objects[poing_obj_id], 24);
        blackFist->offset_bx = 60;
        blackFist->offset_by = 48;
        blackFist->offset_hy = 32;
        blackFist->hit_points = 1;
        blackFist->hit_sprite = 254;
        set_main_and_sub_etat(blackFist, 5, 1);
        blackFist->type = TYPE_BLACK_FIST;
        first_obj_init(blackFist);
        obj_init(blackFist);
    }

    // Get Dark Rayman
    blackRay = &level.objects[black_ray_obj_id];

    // If we want him enabled and he's dead then we have to re-enable him
    if (isEnabled && (blackRay->flags & OBJ_ALIVE) == 0)
    {
        blackRay->flags |= (OBJ_ALIVE | OBJ_ACTIVE);
        blackRay->hit_points = 0xfe;
        set_main_and_sub_etat(blackRay, 0, 0);
        blackRay->x_pos = 0;
        blackRay->y_pos = 0;
        blackRay->init_x_pos = ray.x_pos;
        blackRay->init_y_pos = ray.y_pos;
        blackRay->display_prio = 0;

        ray_stack_is_full = 0;
        ray_pos_in_stack = 0;
        black_pos_in_stack = 0;
    }
    // If we want him disabled and he's alive then we have to disable him
    else if (!isEnabled && (blackRay->flags & OBJ_ALIVE) != 0)
    {
        blackRay->flags &= ~(OBJ_ALIVE|OBJ_ACTIVE);
        blackRay->speed_x = 0;
        blackRay->speed_y = 0;
        DO_NOVA(blackRay);
        level.objects[black_fist_obj_id].flags &= ~(OBJ_ALIVE|OBJ_ACTIVE);
    }
}
