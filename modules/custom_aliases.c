#include <utils.h>

char *is_alias(char **command_args)
{
    for (int i = 0; i < num_aliases; i++)
        printf("%s | %s : %s\n", alias_list[i], alias_map[i], command_args[0]);
        // if (strcmp(alias_list[i], command_args[0]) == 0)
    //         return alias_map[i];
    return NULL;
}

void add_alias(char *key, char *value)
{
    if (num_aliases >= MAX_NUM_ALIASES)
    {
        printf("Can't store more than %d aliases\n", MAX_NUM_ALIASES);
        return;
    }

    *(alias_list + num_aliases) = key;
    *(alias_map + num_aliases) = value;
    num_aliases++;
}
