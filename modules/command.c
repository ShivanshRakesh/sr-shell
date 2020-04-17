#include <utils.h>

char *get_command(void)
{
    size_t bufsize = 0;
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
            perror("EOF of STDIN");
            exit(EXIT_FAILURE);
        }
    }

    if (input[strlen(input) - 1] == '\n')
        input[strlen(input) - 1] = 0;

    store_cmd_in_history(input);

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