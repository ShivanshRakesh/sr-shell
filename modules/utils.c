#include <utils.h>

short is_arrow_key(char *cmd)
{
    if (strlen(cmd) < 3 || cmd[0] != 27 || cmd[1] != 91)
        return 0;
    if (cmd[2] >= 65 && cmd[2] <= 68)
        return cmd[2];
    return 0;
}