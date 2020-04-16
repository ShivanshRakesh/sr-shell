#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <string.h>
#include "print_dialogues.h"
#include "prompt.h"

#define CLRSCR() printf("\033[H\033[J")

char *get_command(void)
{
    ssize_t bufsize = 0;
    char *input;
    if (getline(&input, &bufsize, stdin) == -1)
    {
        if (feof(stdin))
        {
            display_end_note();
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }
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

void fork_and_execute(char **command_args)
{
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

void interact_util(void)
{
    char **command_args = malloc(_SC_NL_ARGMAX * sizeof(char *));
    get_and_parse_command(command_args);
    fork_and_execute(command_args);
    free(command_args);
}

int main()
{
    CLRSCR();
    display_init_dialogue();
    while (1)
    {
        show_prompt();
        interact_util();
    }
    return 0;
}