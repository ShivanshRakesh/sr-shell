#include <utils.h>

void substitute_if_alias(char **command_args)
{
    if (!command_args[0])
        return;
    char *tmp = (char *)malloc(MAX_CMD_LEN * sizeof(char));
    for (int i = 0; i < num_aliases; i++)
    {
        if (strcmp(alias_list[i], command_args[0]) == 0)
        {
            strcpy(tmp, alias_map[i]);
            parse_command(tmp, command_args);
            return;
        }
    }
}

void add_alias(char *key, char *value, short display)
{
    for (int i = 0; i < num_aliases; i++)
    {
        if (strcmp(alias_list[i], key) == 0)
        {
            printf("\033[33malias: alias \033[0m%s\033[33m already exists for \033[0m%s\n", alias_list[i], alias_map[i]);
            return;
        }
    }

    if (num_aliases >= MAX_NUM_ALIASES)
    {
        printf("alias: can't store more than %d aliases\n", MAX_NUM_ALIASES);
        return;
    }

    char *key_tmp = (char *)malloc(MAX_CMD_LEN * sizeof(char));
    char *val_tmp = (char *)malloc(MAX_CMD_LEN * sizeof(char));

    strcpy(key_tmp, key);
    strcpy(val_tmp, value);

    *(alias_list + num_aliases) = key_tmp;
    *(alias_map + num_aliases) = val_tmp;

    num_aliases++;

    if (display)
        printf("\033[33mAdded ALIAS: \033[0m%s\033[33m for COMMAND: \033[0m%s\n", key, value);
}