#include <utils.h>

char *get_history_file_loc(void)
{
    char *history_file_loc;
    history_file_loc = home_dir;
    strcat(history_file_loc, "/");
    strcat(history_file_loc, HISTORY_FILENAME);
    return history_file_loc;
}

void store_cmd_in_history(char *command)
{
    if (command[strlen(command) - 1] == '\n')
        command[strlen(command) - 1] = 0;
    FILE *hist_file = fopen(hist_file_loc, "a+");
    fprintf(hist_file, "%s\n", command);
    fclose(hist_file);
}

void show_history(void)
{
    int hist_num = 1;
    char line[MAX_CMD_LEN];
    FILE *hist_file = fopen(hist_file_loc, "r");
    while (fgets(line, MAX_CMD_LEN, hist_file) != NULL)
    {
        printf("%3d %s", hist_num++, line);
    }
    fclose(hist_file);
}

void clean_history(void)
{
    FILE *hist_file = fopen(hist_file_loc, "w");
    fclose(hist_file);
}

void recall_from_history(char line[], short num)
{
    FILE *hist_file = fopen(hist_file_loc, "r");
    short line_cnt = 0, pos_in_file;

    if (!fseek(hist_file, 0, SEEK_END))
    {
        pos_in_file = ftell(hist_file);
        while (pos_in_file)
            if (!fseek(hist_file, --pos_in_file, SEEK_SET))
                if (fgetc(hist_file) == '\n')
                    if (line_cnt++ == num)
                        break;
        if (pos_in_file)
            fgets(line, MAX_CMD_LEN, hist_file);
    }
    fclose(hist_file);
}

void recall_from_history_util(char **command_args)
{
    if (!command_args[0])
    {
        if (history_mode == RECALL_UP)
        {
            if ((up_arrow + 1) - down_arrow <= 0)
                ALREADY_AT_LATEST_PRINT
            else
            {
                at_latest = 0;
                char recall_res[MAX_CMD_LEN];
                recall_from_history(recall_res, ++up_arrow - down_arrow);
                RECALL_PRINT_1(recall_res);
            }
        }
        else if (history_mode == RECALL_DOWN)
        {
            if (up_arrow - (down_arrow + 1) <= 0)
                ALREADY_AT_LATEST_PRINT
            else
            {
                at_latest = 0;
                char recall_res[MAX_CMD_LEN];
                recall_from_history(recall_res, up_arrow - ++down_arrow);
                RECALL_PRINT_1(recall_res);
            }
        }
    }
    else
    {
        char recall_res[MAX_CMD_LEN];
        switch (is_arrow_key(command_args[0]))
        {
        case UP_ARROW_CODE: // RECALL UPWARDS
            if ((up_arrow + 1) - down_arrow <= 0)
                ALREADY_AT_LATEST_PRINT
            else
            {
                at_latest = 0;
                recall_from_history(recall_res, ++up_arrow - down_arrow);
                if (history_mode == 0)
                    RECALL_PRINT_3(recall_res);
                else
                    RECALL_PRINT_2(recall_res);
            }
            history_mode = RECALL_UP;
            break;

        case DOWN_ARROW_CODE: // RECALL DOWNWARDS
            if (up_arrow - (down_arrow + 1) <= 0)
                ALREADY_AT_LATEST_PRINT
            else
            {
                at_latest = 0;
                recall_from_history(recall_res, up_arrow - ++down_arrow);
                RECALL_PRINT_2(recall_res);
            }
            history_mode = RECALL_DOWN;
            break;

        case RIGHT_ARROW_CODE: // EXECUTE THE RECALLED COMMAND
            recall_from_history(recall_res, up_arrow - down_arrow);
            store_cmd_in_history(recall_res);
            parse_command(recall_res, command_args);
            if (strcmp(command_args[0], "history") == 0)
                show_history();
            else
                fork_and_execute(command_args);
            history_mode = 0;
            up_arrow = 0;
            down_arrow = 0;
            break;

        case LEFT_ARROW_CODE: // EXIT FROM RECALL MODE
            printf("\033[A%c[2K\r", 27);
            history_mode = 0;
            up_arrow = 0;
            down_arrow = 0;
            break;

        default:
            break;
        }
    }
}