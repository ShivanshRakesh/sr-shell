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

            // INPUT REDIRECTION
            char *input_filename = (char *)malloc(MAX_CMD_LEN * sizeof(char));
            if (check_for_input_redir(command_args, input_filename))
            {
                int in_fd = open(input_filename, O_RDONLY);
                dup2(in_fd, 0);
                close(in_fd);
            }

            // OUTPUT REDIRECTION
            char *output_filename = (char *)malloc(MAX_CMD_LEN * sizeof(char));
            if (check_for_output_redir(command_args, output_filename))
            {
                int out_fd = open(output_filename, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                dup2(out_fd, 1);
                close(out_fd);
            }

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

void fork_and_execute_helper(char *command, char **command_args)
{
    // CREATING A COPY OF INPUT COMMAND TO STORE IN HISTORY
    // SINCE COMMAND WOULD GET CHANGED ON PARSING (by strtok)
    char command_cpy[_SC_NL_ARGMAX];
    strcpy(command_cpy, command);

    parse_command(command, command_args);
    substitute_if_alias(command_args);

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

    // TAKE NECESSARY STEPS IN CASE OF ALIAS COMMAND
    else if (strcmp(command_args[0], "alias") == 0)
    {
        store_cmd_in_history(command_cpy);

        char *parsed;
        parsed = strtok(command_cpy, " \n");
        parsed = strtok(NULL, "\n");
        parsed = strtok(parsed, "=");
        command_args[1] = parsed;
        parsed = strtok(NULL, "\"");
        command_args[2] = parsed;

        if (command_args[1] && command_args[2])
            add_alias(command_args[1], command_args[2], 1);
        else
            printf("alias: there was some problem registering this alias\n");
    }

    // FORK AND EXECUTE COMMAND
    else
    {
        store_cmd_in_history(command_cpy);
        fork_and_execute(command_args);
    }
}

void interact_util(void)
{
    if (!history_mode)
        show_prompt();

    char **command_args = malloc(_SC_NL_ARGMAX * sizeof(char *));
    char *command = get_command();

    fork_and_execute_helper(command, command_args);

    NEWLINE();
    free(command_args);
}