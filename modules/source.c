#include <utils.h>

char *get_rc_file_loc(void)
{
    char *rc_file_loc, home_dir_tmp[1024];
    strcpy(home_dir_tmp, getenv("HOME"));
    rc_file_loc = home_dir_tmp;
    strcat(rc_file_loc, "/");
    strcat(rc_file_loc, RC_FILENAME);
    return rc_file_loc;
}

void source_util(char *file_loc)
{
    char line[MAX_CMD_LEN];
    FILE *source_file = fopen(file_loc, "r");
    if (!source_file){
        perror("source");
        return;
    }
    while (fgets(line, MAX_CMD_LEN, source_file) != NULL)
    {
        char **command_args = malloc(_SC_NL_ARGMAX * sizeof(char *));
        fork_and_execute_helper(line, command_args);
        free(command_args);
    }
    fclose(source_file);
}