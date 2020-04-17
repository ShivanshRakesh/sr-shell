#ifndef HISTORY_H_
#define HISTORY_H_

#define HISTORY_FILENAME ".srshell_hist"

short up_arrow;
short down_arrow;
short enter_cnt;

short history_mode;

char *get_history_file_loc(void);
void store_cmd_in_history(char *command);
void show_history(void);

#endif