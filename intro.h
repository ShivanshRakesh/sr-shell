#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#define INTRO_TEXT "\033[1mMade with \033[1;31m\u2764\033[0m\033[1m  by ShivanshRakesh.\n"
#define INTRO_4 " \\_/\\_/\\___|_\\__\\___/_|_|_\\___|  \\__\\___/ |___/_|_\\    |___/_||_|___|____|____| \033[5m[]\033[25m\n"
#define INTRO_3 "\\ V  V / -_) / _/ _ \\ '  \\/ -_) |  _/ _ \\ \\__ \\   /|__|\\__ \\ __ | _|| |__| |__ \n"
#define INTRO_2 "__ __ _____| |__ ___ _ __  ___  | |_ ___  / __| _ \\ __ / __| || | __| |  | |   \n"
#define INTRO_1 "            _                    _         ___ ___      ___ _  _ ___ _    _    \n"

#define PRINT_DASHED_LINE(n)           \
    printf("\033[1m");                 \
    for (short i = (n)-1; i >= 0; i--) \
    {                                  \
        printf("-");                   \
        if (!i)                        \
            printf("\n");              \
    }                                  \
    printf("\033[0m");

#define PRINT_INTRO_BANNER(n)              \
    printf("\033[1m%*s%*s%*s%*s\033[0m\n", \
           ((n) + 80) / 2, INTRO_1,        \
           ((n) + 80) / 2, INTRO_2,        \
           ((n) + 80) / 2, INTRO_3,        \
           ((n) + 80) / 2 + 12, INTRO_4);

#define PRINT_INTRO_TEXT(n) printf("%*s\033[0m", ((n) + 34) / 2 + 21, INTRO_TEXT);

void display_init_dialogue();

#endif