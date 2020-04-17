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