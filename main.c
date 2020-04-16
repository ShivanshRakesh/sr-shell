#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <string.h>
#include <limits.h>
#include "intro.h"

#define CLRSCR() printf("\033[H\033[J")
#define PROMPT_RIGHT "SR-SHELL\0"

char *get_command()
{
    ssize_t bufsize = 0;
    char *input;
    getline(&input, &bufsize, stdin);
    return input;
}

void get_and_parse_command(char **command_args)
{
    char *parsed, *delim = " \n";
    int indx = 0;

    parsed = strtok(get_command(), delim);
    while (parsed != NULL)
    {
        command_args[indx++] = parsed;
        parsed = strtok(NULL, delim);
    }
    command_args[indx] = NULL;
}

void fork_and_execute(char **command_args){
    int stat_loc, status;
    pid_t child_pid, wait_res;
    child_pid = fork();
    if (child_pid == 0)
    {
        status = execvp(command_args[0], command_args);
        printf("Status: %d\n\n", status);
    }
    else
    {
        wait_res = waitpid(child_pid, &stat_loc, WUNTRACED);
        printf("\n");
    }
}

void show_prompt()
{
    short m[4];
    ioctl(0, 21523, m);
    char *hostname;
    if ((hostname = (char *)malloc(_SC_HOST_NAME_MAX)) != NULL)
        gethostname(hostname, _SC_HOST_NAME_MAX);
    short spacing = m[1] - 4 - strlen(getenv("USER")) - strlen(getenv("PWD")) - strlen(hostname);
    printf("\033[1;32m%s@%s:\033[0;36m %s\033[0;32m%*s\n\033[1;36m> ", getenv("USER"), hostname, getenv("PWD"), spacing, PROMPT_RIGHT);
    printf("\033[0m");
    free(hostname);
}

int main()
{
    CLRSCR();
    display_init_dialogue();
    while (1)
    {
        show_prompt();
        char **command_args = malloc(64 * sizeof(char *));
        get_and_parse_command(command_args);
        fork_and_execute(command_args);
        free(command_args);
    }
    return 0;
}