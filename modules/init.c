#include <utils.h>

void init(void)
{
    home_dir = getenv("HOME");
    
    // HISTORY INITIALIZATIONS
    hist_file_loc = get_history_file_loc();
    at_latest = 0;
    up_arrow = 0;
    down_arrow = 0;
    history_mode = 0;

    CLRSCR();
    display_init_dialogue();
}