#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <string.h>
#include <signal.h>

#include <command.h>
#include <history.h>
#include <init.h>
#include <print_dialogues.h>
#include <process.h>
#include <prompt.h>

#define CLRSCR() printf("\033[H\033[J")
#define NEWLINE() printf("\n")
#define JAB_TAK_HAI_JAAN while(1)   // Language:Hindi; Alternative for:'Until Dead'; #justForFun

#endif