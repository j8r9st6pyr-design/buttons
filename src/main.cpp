#include "main.h"
#include "pros/apix.h" // Required to unlock full LVGL functionality

// Shared variable that will be altered by your buttons
static int autonomous_mode = 0; 

// Event callback to handle button presses
static lv_res_t btnm_variable_cb(lv_obj_t * obj, uint16_t id)
{
    // Assign different values based on the button index (0, 1, or 2)
    switch(id) {
        case 0:
            autonomous_mode = 10;   // "Left" mode
            break;
        case 1:
            autonomous_mode = 50;   // "Center" mode
            break;
        case 2:
            autonomous_mode = 100;  // "Right" mode
            break;
        default:
            break;
    }

    // Print to the terminal for debugging
    printf("Auton updated! Mode = %d\n", autonomous_mode);

    return LV_RES_OK; // Required return type for LVGL v8 actions
}

void initialize() {
    // IMPORTANT: Remove pros::lcd::initialize() or LLEMU code 
    // Custom LVGL layouts cannot run at the same time as the legacy LCD emulator.

    // 1. Define a 1x3 button map
    static const char * btnm_map[] = {"Left Auton", "Center Auton", "Right Auton", ""};

    // 2. Create the Button Matrix on the active screen
    lv_obj_t * btnm = (lv_obj_t *)lv_btnmatrix_create(lv_scr_act(), NULL);
    lv_btnmatrix_set_map(btnm, btnm_map);

    // 3. Size it to fit nicely on the V5 Brain screen (480 x 272 resolution)
    lv_obj_set_size(btnm, 400, 60);
    lv_obj_align(btnm, NULL, LV_ALIGN_CENTER, 0, 0);

    // 4. Transform it into a radio button group (only one active at a time)
    lv_btnmatrix_set_one_toggle(btnm, true);
    
    // Check the first button ("Left Auton") by default
    lv_btnmatrix_set_btn_ctrl(btnm, 0, LV_BTNMATRIX_CTRL_TGL_ENABLE);
    lv_btnmatrix_set_btn_ctrl(btnm, 0, LV_BTNMATRIX_CTRL_CHECKED);
    lv_btnmatrix_set_btn_ctrl(btnm, 1, LV_BTNMATRIX_CTRL_TGL_ENABLE);
    lv_btnmatrix_set_btn_ctrl(btnm, 2, LV_BTNMATRIX_CTRL_TGL_ENABLE);

    // 5. Assign the callback function to handle clicks
    lv_btnmatrix_set_action(btnm, (lv_btnmatrix_action_t)btnm_variable_cb);
}
