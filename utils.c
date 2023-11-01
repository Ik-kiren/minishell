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

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return i;
}

char *ft_strdup(char *str)
{
    char *tmp;
    int len;
    int i;

    i = 0;
    len = ft_strlen(str);
    tmp = malloc(sizeof(char) * len);
    while (str[i])
    {
        tmp[i] = str[i];
        i++;
    }
    tmp[i] = '\0';
    return tmp;
}

int free_ptr(char **ptr)
{
    int i;

    i = 0;
    while (ptr[i])
    {
        free(ptr[i++]);
    }
    free(ptr);
    return 1;
}

char **ft_ptrjoin(char *s1, char **s2)
{
    char **tmp;
    int len;
    int i;

    i = 0;
    len = ft_ptrlen(s2);
    tmp = malloc(sizeof(char *) * len);
    while (s2[i])
    {
        tmp[i] = ft_strdup(s2[i]);
        i++;
    }
    tmp[len] = s1;
    tmp[len + 1] = NULL;
    printf("export = %s\n", tmp[len]);
    printf("export+1 = %s\n", tmp[len + 1]);
    free_ptr(s2);
    return tmp;
}

void get_allenv(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        printf("%d\n", i);
        printf("%s\n", envp[i]);
        i++;
    }
}