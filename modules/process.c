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
        // if (WIFEXITED(stat_loc) && WEXITSTATUS(stat_loc) == 0){
        //     printf("Process exited normally.");
        // }

        if (WIFSIGNALED(stat_loc))
            NEWLINE();
        // printf("\nSignal encountered: %d\n", WTERMSIG(stat_loc));
    }
}

#define UP_ARROW_CODE 65
#define DOWN_ARROW_CODE 66
#define RIGHT_ARROW_CODE 67
#define LEFT_ARROW_CODE 68

#define RECALL_UP 1
#define RECALL_DOWN 2
short at_latest = 0;

short is_arrow_key(char *cmd)
{
    if (strlen(cmd) < 3 || cmd[0] != 27 || cmd[1] != 91)
        return 0;
    if (cmd[2] >= 65 && cmd[2] <= 68)
        return cmd[2];
    return 0;
}

void recall_from_history(char line[], short num)
{
    // printf("\n\n\nhere%d", num);
    FILE *hist_file = fopen(hist_file_loc, "r");
    short line_cnt = 0, pos_in_file;

    if (!fseek(hist_file, 0, SEEK_END))
    {
        pos_in_file = ftell(hist_file);
        while (pos_in_file)
        {
            if (!fseek(hist_file, --pos_in_file, SEEK_SET))
                if (fgetc(hist_file) == '\n')
                    if (line_cnt++ == num+1){
                        // printf("n reached");
                        break;
                    }
        }
        if(pos_in_file)
            fgets(line, MAX_CMD_LEN, hist_file);
    }
    fclose(hist_file);
}

void interact_util(void)
{
    if (!history_mode)
        show_prompt();
    char **command_args = malloc(_SC_NL_ARGMAX * sizeof(char *));
    char *command = get_command();
    parse_command(command, command_args);

    if (command_args[0] == NULL)
    {
        if (history_mode == RECALL_UP)
        {
            char arr[MAX_CMD_LEN];
            up_arrow++;
            if(up_arrow-down_arrow <= 0)
                printf("Already at the latest command!\n");
            else{
                recall_from_history(arr, up_arrow - down_arrow);
                // printf("\033[A");
                printf("\033[A\033[A%c[2K\r\033[1;36m> \033[0m\033[33m%s\033[0m\033[A", 27, arr);
            }
        }
        else if (history_mode == RECALL_DOWN)
        {
            char arr[MAX_CMD_LEN];
            down_arrow++;
            if(up_arrow-down_arrow <= 0){
                if(!at_latest){
                    at_latest = 1;
                    printf("\033[A\033[33mAlready at the latest command!\033[0m");
                    printf("\n\r\033[1;36m> \033[0m");
                }
                else
                    printf("\033[A\033[A\r\033[1;36m> \033[0m");
            }
            else{
                recall_from_history(arr, up_arrow - down_arrow);
                printf("\033[A\033[A%c[2K\r\033[1;36m> \033[0m\033[33m%s\033[0m\033[A", 27, arr);
            }
        }
    }

    else if (strcmp(command_args[0], "history") == 0)
        show_history();

    else if (is_arrow_key(command_args[0]))
    {
        char arr[MAX_CMD_LEN];
        switch (is_arrow_key(command_args[0]))
        {
        case UP_ARROW_CODE:
            up_arrow++;
            recall_from_history(arr, up_arrow - down_arrow);
            if(history_mode == 0)
                printf("\033[A%c[2K\r\033[1;36m> \033[0m%s \033[A(up %d command(s))", 27, arr, up_arrow - down_arrow);
            else
                printf("\033[A%c[2K\033[A%c[2K\r\033[1;36m> \033[0m%s \033[A(up %d command(s))", 27, 27, arr, up_arrow - down_arrow);
            history_mode = RECALL_UP;
            break;
        case DOWN_ARROW_CODE:
            down_arrow++;
            recall_from_history(arr, up_arrow - down_arrow);
            history_mode = RECALL_DOWN;
            printf("\033[A%c[2K\033[A%c[2K\r\033[1;36m> \033[0m%s\033[A", 27, 27, arr);
            break;
        case RIGHT_ARROW_CODE:
            history_mode = 0;
            // char cmd[] = recall_from_history(up_arrow-down_arrow);
            char c[] = "ls -l";
            parse_command(c, command_args);
            fork_and_execute(command_args);
            up_arrow = 0;
            down_arrow = 0;
            break;
        default:
            break;
        }
    }

    else{
        store_cmd_in_history(command);
        fork_and_execute(command_args);
    }

    NEWLINE();
    free(command_args);
}