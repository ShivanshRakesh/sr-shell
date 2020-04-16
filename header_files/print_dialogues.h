#ifndef PRINT_DIALOGUE_H_
#define PRINT_DIALOGUE_H_

#define INTRO_TEXT "\033[1mMade with \033[1;31m\u2764\033[0m\033[1m by ShivanshRakesh.\n"
#define END_NOTE "\033[1;36mBye! Though I'm sad to see you leave.. :(\033[0m\n"
#define INTRO_4 " \\_/\\_/\\___|_\\__\\___/_|_|_\\___|  \\__\\___/ |___/_|_\\    |___/_||_|___|____|____|\n"
#define INTRO_3 "\\ V  V / -_) / _/ _ \\ '  \\/ -_) |  _/ _ \\ \\__ \\   /|__|\\__ \\ __ | _|| |__| |__ \n"
#define INTRO_2 "__ __ _____| |__ ___ _ __  ___  | |_ ___  / __| _ \\ __ / __| || | __| |  | |   \n"
#define INTRO_1 "            _                    _         ___ ___      ___ _  _ ___ _    _    \n"

#define PRINT_DASHED_LINE(n)           \
    printf("\033[0m\r");               \
    for (short i = (n)-1; i >= 0; i--) \
    {                                  \
        printf("-");                   \
        if (!i)                        \
            NEWLINE();              \
    }                                  \
    printf("\033[0m");

#define PRINT_INTRO_BANNER(n)              \
    printf("\033[1m%*s%*s%*s%*s\033[0m\n", \
           ((n) + 80) / 2 + 1, INTRO_1,    \
           ((n) + 80) / 2 + 1, INTRO_2,    \
           ((n) + 80) / 2 + 1, INTRO_3,    \
           ((n) + 80) / 2 + 1, INTRO_4);

#define PRINT_INTRO_TEXT(n) printf("%*s\033[0m", ((n) + 35) / 2 + 20, INTRO_TEXT);

#define PRINT_END_NOTE(n)                         \
    PRINT_DASHED_LINE(m[1]);                      \
    printf("%*s", ((n) + 42) / 2 + 12, END_NOTE); \
    PRINT_DASHED_LINE(m[1]);                      \
    NEWLINE();

short m[4];

void display_init_dialogue(void);
void display_end_note(void);

#endif