#include <utils.h>

void fork_and_execute(char **command_args)
{
    signal(SIGINT, SIG_IGN);

    int stat_loc, status;
    pid_t child_pid;

    child_pid = fork();

    if (child_pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        status = execvp(command_args[0], command_args);
        if (status < 0)
        {
            perror(command_args[0]);
            exit(1);
        }
    }
    else
    {
        waitpid(child_pid, &stat_loc, WUNTRACED);
        NEWLINE();
        // if (WIFEXITED(stat_loc) && WEXITSTATUS(stat_loc) == 0){
        //     printf("Process exited normally.");
        // }

        if (WIFSIGNALED(stat_loc))
            NEWLINE();
        // printf("\nSignal encountered: %d\n", WTERMSIG(stat_loc));
    }
}

void interact_util(void)
{
    show_prompt();
    char **command_args = malloc(_SC_NL_ARGMAX * sizeof(char *));
    get_and_parse_command(command_args);
    fork_and_execute(command_args);
    free(command_args);
}