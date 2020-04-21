#include <utils.h>

void init(void)
{
    home_dir = getenv("HOME");
    num_aliases = 0;
    alias_list = (char **)malloc(MAX_NUM_ALIASES * sizeof(char *));
    alias_map = (char **)malloc(MAX_NUM_ALIASES * sizeof(char *));

    // HISTORY INITIALIZATIONS
    at_latest = 0;
    up_arrow = 0;
    down_arrow = 0;
    history_mode = 0;

    // SOURCING THE SRSHELL_RC FILE
    fopen(get_rc_file_loc(), "a+");
    source_util(get_rc_file_loc());

    // CLRSCR();
    // display_init_dialogue();
}