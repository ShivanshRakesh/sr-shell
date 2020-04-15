#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <string.h> 

#define clear() printf("\033[H\033[J") 

int main(){
    clear();
    size_t __size = pathconf(".", _PC_PATH_MAX);
    char *buf;
    char *pwd;
    
    if ((buf = (char *)malloc(__size)) != NULL)
        pwd = getcwd(__buf, __size);

    printf("> %s", pwd);

    ssize_t bufsize = 0;
    char *input;
    char **command = malloc(64 * sizeof(char *));
    char *parsed;
    char *delim = " \n";
    int indx = 0;
    getline(&input, &bufsize, stdin);
    parsed = strtok(input, delim); 
    while (parsed != NULL) {
        command[indx++] = parsed;
        parsed = strtok(NULL, delim);
    }
    command[indx] = NULL;

    pid_t child_pid = fork();
    int stat_loc, status;
    pid_t wait_res;
    // char *argv[] = {"ls", "-la", NULL};
    if (child_pid == 0) {
        status = execvp(command[0], command);
        printf("status: %d", status);
    }
    else {
        wait_res = waitpid(child_pid, &stat_loc, WUNTRACED);
        printf("\n"); 
    }

    return 0;
}