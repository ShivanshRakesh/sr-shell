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

#include "prompt.h"
#include "print_dialogues.h"
#include "command.h"
#include "process.h"

#define CLRSCR() printf("\033[H\033[J")

#endif