#ifndef BUILTINS_H_
#define BUILTINS_H_

short is_builtin(char **);
short builtin_cd(char **);
short builtin_quit(char **);

#define NUM_BUILTINS sizeof(builtin_cmd_list) / sizeof(char *)

#endif