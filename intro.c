#include <sys/ioctl.h>
#include <stdio.h>
#include "intro.h"

void display_init_dialogue()
{
    short m[4];
    ioctl(0, 21523, m);
    printf("\n");
    PRINT_DASHED_LINE(m[1]);
    PRINT_INTRO_BANNER(m[1]);
    PRINT_DASHED_LINE(m[1]);
    PRINT_INTRO_TEXT(m[1]);
    PRINT_DASHED_LINE(m[1]);
    printf("\n\033[0m");
}
