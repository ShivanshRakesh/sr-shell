#ifndef UTILS_H_
#define UTILS_H_

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <builtins.h>
#include <command.h>
#include <custom_aliases.h>
#include <history.h>
#include <init.h>
#include <print_dialogues.h>
#include <process.h>
#include <prompt.h>
#include <redirect.h>
#include <source.h>

#define CLRSCR() printf("\033[H\033[J")
#define NEWLINE() printf("\n")
#define JAB_TAK_HAI_JAAN while (1) // Language:Hindi; Alternative for:'Until Dead'; #justForFun

#define UP_ARROW_CODE 65
#define DOWN_ARROW_CODE 66
#define RIGHT_ARROW_CODE 67
#define LEFT_ARROW_CODE 68
short is_arrow_key(char *);

#endif