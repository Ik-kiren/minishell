#include "minishell.h"

size_t ft_ptrlen(char **str)
{
    int i;

    while (str[i])
        i++;
    return i;
}

char **ft_ptrjoin(char *s1, char **s2)
{
    char **tmp;
    size_t len;

    len = ft_ptrlen(s2);
    tmp = malloc(sizeof(char) * len + 2);
    tmp[len + 1] = s1;
    tmp[len + 2] = NULL;
    printf("export = %s\n", tmp[len + 1]);
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