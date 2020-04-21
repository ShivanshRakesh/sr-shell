#ifndef PROCESS_H_
#define PROCESS_H_

// char line[MAX_CMD_LEN];

void fork_and_execute(char **);
void fork_and_execute_helper(char *, char **);
void interact_util(void);
void recall_from_history(char*, short);
short is_arrow_key(char *);

#endif