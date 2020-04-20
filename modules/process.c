#include <utils.h>

void fork_and_execute(char **command_args)
{
    signal(SIGINT, SIG_IGN); // TO IGNORE THE CTRL+C IN PARENT SHELL PROCESS

    if (!is_builtin(command_args))
    {
        int stat_loc, status;
        pid_t child_pid;

        child_pid = fork();

        if (child_pid == 0)
        {
            signal(SIGINT, SIG_DFL); // RESTORE THE FUNCTIONALITY OF CTRL+C IN CHILD PROCESS
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
            // if (WIFEXITED(stat_loc) && WEXITSTATUS(stat_loc) == 0){
            //     printf("Process exited normally.");
            // }

            if (WIFSIGNALED(stat_loc))
                NEWLINE();
            // printf("\nSignal encountered: %d\n", WTERMSIG(stat_loc));
        }
    }
}

void interact_util(void)
{
    if (!history_mode)
        show_prompt();

    char **command_args = malloc(_SC_NL_ARGMAX * sizeof(char *));
    char *command = get_command();

    // CREATING A COPY OF INPUT COMMAND TO STORE IN HISTORY
    // SINCE COMMAND WOULD GET CHANGED ON PARSING (by strtok)
    char command_cpy[_SC_NL_ARGMAX];
    strcpy(command_cpy, command);

    parse_command(command, command_args);

    // EITHER IN RECALLING FROM HISTORY OR AN EMPTY COMMAND
    if (command_args[0] == NULL)
    {
        if (history_mode)
            recall_from_history_util(command_args);
    }

    // BROWSE THROUGH COMMAND HISTORY
    else if (is_arrow_key(command_args[0]))
        recall_from_history_util(command_args);

    // COMMANDS RELATED TO COMMAND HISTORY
    else if (strcmp(command_args[0], "history") == 0)
    {
        store_cmd_in_history(command_cpy);
        if (command_args[1] && strcmp(command_args[1], "clean") == 0)
            clean_history();
        else
            show_history();
    }

    // FORK AND EXECUTE COMMAND
    else
    {
        store_cmd_in_history(command_cpy);
        fork_and_execute(command_args);
    }

    NEWLINE();
    free(command_args);
}