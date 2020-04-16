#include <sys/ioctl.h>
#include <stdio.h>
#include "print_dialogues.h"

void display_init_dialogue(void)
{
    ioctl(0, 21523, m);
    printf("\n");
    PRINT_DASHED_LINE(m[1]);
    PRINT_INTRO_BANNER(m[1]);
    PRINT_DASHED_LINE(m[1]);
    PRINT_INTRO_TEXT(m[1]);
    PRINT_DASHED_LINE(m[1]);
    printf("\n\033[0m");
}

void display_end_note(void)
{
    ioctl(0, 21523, m);
    printf("\033[A\r");
    PRINT_END_NOTE(m[1]);
}