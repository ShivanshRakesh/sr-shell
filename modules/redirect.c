#include <utils.h>

short check_for_input_redir(char **command_args, char *input_file)
{
    for (int itr1 = 0; command_args[itr1] != NULL; itr1++)
    {
        if (command_args[itr1][0] == '<')
        {
            if (command_args[itr1 + 1] != NULL)
                strcpy(input_file, command_args[itr1 + 1]);
            else
            {
                printf("Input redirection: expected an input file\n");
                return 0;
            }

            for (int itr2 = itr1; command_args[itr2 - 1] != NULL; itr2++)
                command_args[itr2] = command_args[itr2 + 2];

            return 1;
        }
    }
    return 0;
}

short check_for_output_redir(char **command_args, char *output_file)
{
    for (int itr1 = 0; command_args[itr1] != NULL; itr1++)
    {
        if (strcmp(command_args[itr1], ">") == 0)
        {
            if (command_args[itr1 + 1] != NULL)
                strcpy(output_file, command_args[itr1 + 1]);
            else
            {
                printf("Output redirection: expected an output file\n");
                return 0;
            }

            for (int itr2 = itr1; command_args[itr2 - 1] != NULL; itr2++)
                command_args[itr2] = command_args[itr2 + 2];

            return 1;
        }
    }
    return 0;
}