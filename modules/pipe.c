#include <utils.h>

int check_for_pipe(char **command_args)
{
    for (int itr = 0; command_args[itr] != NULL; itr++)
    {
        if (command_args[itr][0] == '|')
        {
            if (itr != 0 && command_args[itr + 1] != NULL)
            {
                command_args[itr] = NULL;
                return itr + 1;
            }
            else
            {
                printf("Pipe: expected commands on both sides of the pipe\n");
                return 0;
            }
        }
    }
    return 0;
}