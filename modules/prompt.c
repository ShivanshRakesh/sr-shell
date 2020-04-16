#include "../header_files/utils.h"

char *get_git_branch(void)
{
    char *BUF;
    FILE *FP;
    if ((FP = popen("git rev-parse --abbrev-ref HEAD", "r")) == NULL)
        return '\0';
    if ((BUF = (char *)malloc(256)) != NULL)
        while (fgets(BUF, 256, FP) != NULL)
            return BUF;
    pclose(FP);
    printf("\033[A\r");
    return '\0';
}

void show_prompt(void)
{
    short m[4], spacing;
    ioctl(0, 21523, m);
    char *hostname;
    char *git_branch = get_git_branch();
    if (git_branch && git_branch[strlen(git_branch) - 1] == '\n')
        git_branch[strlen(git_branch) - 1] = '\0';
    if ((hostname = (char *)malloc(_SC_HOST_NAME_MAX)) != NULL)
        gethostname(hostname, _SC_HOST_NAME_MAX);
    if (git_branch)
    {
        spacing = m[1] - 7 - strlen(getenv("USER")) - strlen(getenv("PWD")) - strlen(hostname) - strlen(git_branch);
        printf("\033[1;32m%s@%s:\033[0;36m %s \033[0mon \033[1;32m%s\033[0;32m%*s\n\033[1;36m> ", getenv("USER"), hostname, getenv("PWD"), git_branch, spacing, PROMPT_RIGHT);
    }
    else
    {
        spacing = m[1] - 3 - strlen(getenv("USER")) - strlen(getenv("PWD")) - strlen(hostname);
        printf("\033[1;32m%s@%s:\033[0;36m %s\033[0;32m%*s\n\033[1;36m> ", getenv("USER"), hostname, getenv("PWD"), spacing, PROMPT_RIGHT);
    }
    printf("\033[0m");
}