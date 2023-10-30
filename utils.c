#include "minishell.h"

int ft_ptrlen(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        i++;
    }
    return i;
}

char **ft_ptrjoin(char *s1, char **s2)
{
    char **tmp;
    int len;
    int i;

    i = 0;
    len = ft_ptrlen(s2);
    tmp = malloc(sizeof(char) * len + 1);
    while (s2[i])
    {
        tmp[i] = s2[i];
        i++;
    }
    tmp[len] = s1;
    tmp[len + 1] = NULL;
    printf("export = %s\n", tmp[len]);
    return tmp;
}

void get_allenv(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        printf("%s\n", envp[i++]);
    }
}