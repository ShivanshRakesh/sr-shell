#include <utils.h>

void init(void)
{
    home_dir = getenv("HOME");
    hist_file_loc = get_history_file_loc();
    // CLRSCR();
    // display_init_dialogue();
}