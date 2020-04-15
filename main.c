#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <string.h>
#include <limits.h>

#define CLRSCR() printf("\033[H\033[J")
#define PROMPT_RIGHT "SR-SHELL\0"
#define INTRO_TEXT "Made with \033[1;31m\u2764\033[0m\033[1m  by ShivanshRakesh.\n"
#define INTRO_4 " \\_/\\_/\\___|_\\__\\___/_|_|_\\___|  \\__\\___/ |___/_|_\\    |___/_||_|___|____|____| \033[5m[]\033[25m\n"
#define INTRO_3 "\\ V  V / -_) / _/ _ \\ '  \\/ -_) |  _/ _ \\ \\__ \\   //__\\\\__ \\ __ | _|| |__| |__ \n"
#define INTRO_2 "__ __ _____| |__ ___ _ __  ___  | |_ ___  / __| _ \\ __ / __| || | __| |  | |   \n"
#define INTRO_1 "            _                    _         ___ ___      ___ _  _ ___ _    _    \n"

char *get_command()
{
    ssize_t bufsize = 0;
    char *input;
    getline(&input, &bufsize, stdin);
    return input;
}

void get_and_parse_command(char **command_args)
{
    char *parsed, *delim = " \n";
    int indx = 0;

    parsed = strtok(get_command(), delim);
    while (parsed != NULL)
    {
        command_args[indx++] = parsed;
        parsed = strtok(NULL, delim);
    }
    command_args[indx] = NULL;
}

void show_prompt()
{
    short m[4];
    ioctl(0, 21523, m);
    char *hostname;
    if ((hostname = (char *)malloc(_SC_HOST_NAME_MAX)) != NULL)
        gethostname(hostname, _SC_HOST_NAME_MAX);
    short spacing = m[1] - 4 - strlen(getenv("USER")) - strlen(getenv("PWD")) - strlen(hostname);
    printf("\033[1;32m%s@%s:\033[0;36m %s\033[0;32m%*s\n\033[1;36m> ", getenv("USER"), hostname, getenv("PWD"), spacing, PROMPT_RIGHT);
    printf("\033[0m");
}

void display_init_dialogue()
{
    short m[4];
    ioctl(0, 21523, m);
    printf("\033[1m");
    printf("\n");
    for (short i = 0; i < m[1]; i++)
        printf("-");
    printf("%*s", (m[1] + 80) / 2, INTRO_1);
    printf("%*s", (m[1] + 80) / 2, INTRO_2);
    printf("%*s", (m[1] + 80) / 2, INTRO_3);
    printf("%*s", (m[1] + 80) / 2 + 12, INTRO_4);
    printf("\n");
    for (short i = 0; i < m[1]; i++)
        printf("-");

    printf("%*s", (m[1] + 34) / 2 + 17, INTRO_TEXT);
    for (short i = 0; i < m[1]; i++)
        printf("-");
    printf("\n");
    printf("\n");
    printf("\033[0m");
}

double factorial(unsigned n){
    if (n==1) return n;
    return n*factorial(n-1);
}

void delay(int n){
    for(int i=0; i<n; i++){
        factorial(10);
    }
}

// void display_init_dialogue_marquee()
// {
//     short m[4];
//     ioctl(0, 21523, m);
//     for (int j = m[1]; j >= 4; j--)
//     {
//         printf("\033[1m");
//         printf("\n");
//         for (short i = 0; i < m[1]; i++)
//             printf("-");
//         printf("%*s", (m[1] - j), "            _                    _         ___ ___      ___ _  _ ___ _    _    \n");
//         printf("%*s", (m[1] - j), "__ __ _____| |__ ___ _ __  ___  | |_ ___  / __| _ \\ __ / __| || | __| |  | |   \n");
//         printf("%*s", (m[1] - j), "\\ V  V / -_) / _/ _ \\ '  \\/ -_) |  _/ _ \\ \\__ \\   //__\\\\__ \\ __ | _|| |__| |__ \n");
//         printf("%*s", (m[1] - j + 12), " \\_/\\_/\\___|_\\__\\___/_|_|_\\___|  \\__\\___/ |___/_|_\\    |___/_||_|___|____|____| \033[5m[]\033[25m\n");
//         printf("\n");
//         for (short i = 0; i < m[1]; i++)
//             printf("-");
//         printf("\n");
//         printf("\n");
//         printf("\033[0m");
//         CLRSCR();
//         if(j!=4){
//             delay(2e5);
//         }
//     }

//     for (int j = 4; j <= 70; j++)
//     {
//         printf("\033[1m");
//         printf("\n");
//         for (short i = 0; i < m[1]; i++)
//             printf("-");
//         printf("%*s", (m[1] - j), "            _                    _         ___ ___      ___ _  _ ___ _    _    \n");
//         printf("%*s", (m[1] - j), "__ __ _____| |__ ___ _ __  ___  | |_ ___  / __| _ \\ __ / __| || | __| |  | |   \n");
//         printf("%*s", (m[1] - j), "\\ V  V / -_) / _/ _ \\ '  \\/ -_) |  _/ _ \\ \\__ \\   //__\\\\__ \\ __ | _|| |__| |__ \n");
//         printf("%*s", (m[1] - j + 12), " \\_/\\_/\\___|_\\__\\___/_|_|_\\___|  \\__\\___/ |___/_|_\\    |___/_||_|___|____|____| \033[5m[]\033[25m\n");
//         printf("\n");
//         for (short i = 0; i < m[1]; i++)
//             printf("-");
//         printf("\n");
//         printf("\n");
//         printf("\033[0m");
//         CLRSCR();
//         delay(2e5);
//     }
// }

int main()
{
    CLRSCR();
    display_init_dialogue();
    short loop = 1;
    int stat_loc, status;
    pid_t child_pid, wait_res;
    while (loop)
    {
        show_prompt();
        char **command_args = malloc(64 * sizeof(char *));
        get_and_parse_command(command_args);

        child_pid = fork();
        if (child_pid == 0)
        {
            status = execvp(command_args[0], command_args);
            printf("Status: %d\n\n", status);
        }
        else
        {
            wait_res = waitpid(child_pid, &stat_loc, WUNTRACED);
            printf("\n");
        }
    }
    return 0;
}