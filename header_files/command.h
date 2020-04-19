#ifndef COMMAND_H_
#define COMMAND_H_

#define MAX_CMD_LEN 1024

char *get_command(void);
void parse_command(char *, char **);

#endif