#include <utils.h>

char *builtin_cmd_list[] = {
    "cd",
    "quit"
};

short (*builtin_cmd[]) (char **) = {
    &builtin_cd,
    &builtin_quit,
};

short is_builtin(char **command_args)
{
    for (int i = 0; i < NUM_BUILTINS; i++)
        if (strcmp(builtin_cmd_list[i], command_args[0]) == 0){
            return (*builtin_cmd[i])(command_args);
        }
    return 0;
}

short builtin_cd(char **command_args)
{
    if (command_args[1] == NULL){
        if (chdir(home_dir) != 0)
            perror("Error in changing directory");
    }
    else if (chdir(command_args[1]) != 0)
        perror("Error in changing directory");
    return 1;
}

short builtin_quit(char **command_args)
{
    exit(1);
    return 1;
}