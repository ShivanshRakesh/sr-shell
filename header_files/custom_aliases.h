#ifndef ALIASES_H_
#define ALIASES_H_

#define MAX_NUM_ALIASES 50

int num_aliases;
char **alias_list;
char **alias_map;

void substitute_if_alias(char **);
void add_alias(char *, char *, short);

#endif