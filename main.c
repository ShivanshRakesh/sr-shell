#include <utils.h>

int main()
{
    CLRSCR();
    display_init_dialogue();
    while (1)
        interact_util();
    return 0;
}