#ifndef HISTORY_H_
#define HISTORY_H_

#define HISTORY_FILENAME ".srshell_hist"

#define RECALL_UP 1
#define RECALL_DOWN 2

#define RECALL_PRINT_1(arr) printf("\033[A\033[A%c[2K\r\033[1;36m> \033[0m\033[33m%s\033[0m\033[A", 27, (arr))
#define RECALL_PRINT_2(arr) printf("\033[A%c[2K\033[A%c[2K\r\033[1;36m> \033[0m\033[33m%s\033[0m\033[A", 27, 27, (arr))
#define RECALL_PRINT_3(arr) printf("\033[A%c[2K\r\033[1;36m> \033[0m\033[33m%s\033[0m\033[A", 27, (arr))

#define ALREADY_AT_LATEST_PRINT                                        \
    if (!at_latest)                                                    \
    {                                                                  \
        at_latest = 1;                                                 \
        printf("\033[A\033[33mAlready at the latest command!\033[0m"); \
        printf("\n\r\033[1;36m> \033[0m");                             \
    }                                                                  \
    else                                                               \
        printf("\033[A\033[A\r\033[1;36m> \033[0m");

short up_arrow;
short down_arrow;
short at_latest;
short history_mode;

char *get_history_file_loc(void);
void store_cmd_in_history(char *command);
void show_history(void);
void clean_history(void);
void recall_from_history(char *, short);
void recall_from_history_util(char **);

#endif