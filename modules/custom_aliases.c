#include <utils.h>

void substitute_if_alias(char **command_args)
{
    char *tmp = (char*)malloc(MAX_CMD_LEN*sizeof(char));
    for (int i = 0; i < num_aliases; i++){
        if (strcmp(alias_list[i], command_args[0]) == 0){
            strcpy(tmp, alias_map[i]);
            parse_command(tmp, command_args);
            return;
        }
    }
}

void add_alias(char *key, char *value, short display)
{
    for (int i = 0; i < num_aliases; i++){
        if (strcmp(alias_list[i], key) == 0){
            // THERE IS A REASON I DID NOT PRINT THE DUPLICATE KEY. WORKING ON THAT.
            printf("alias: there was some problem registering this alias, might be a duplicate\n");
            return;
        }
    }
    
    if (num_aliases >= MAX_NUM_ALIASES)
    {
        printf("Can't store more than %d aliases\n", MAX_NUM_ALIASES);
        return;
    }

    if(display)
        printf("\033[33mAdded ALIAS: \033[0m%s\033[33m for COMMAND: \033[0m%s\n", key, value);

    *(alias_list + num_aliases) = key;
    *(alias_map + num_aliases) = value;
    num_aliases++;
}
