#include "minishell.h"

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i])
    {
        if (s1[i] != s2[i])
            return 0;
        i++;
    }
    return 1;
}

int shell_cd(char **tokens)
{
    if (tokens[1] == NULL)
        fprintf(stderr, "pathname error");
    else
        if (chdir(tokens[1]) != 0)
          perror("lsh3"); 
    return 1;
}

int shell_echo(char **tokens)
{
    int i;
    int arg;

    i = 1;
    arg = 0;
    while (tokens[i])
    {
        if (ft_strcmp(tokens[i], "-n"))
        {
            printf("%s", tokens[++i]);
            arg++;
        }
        else
            printf("%s", tokens[i]);
        i++;
    }
    if (arg == 0)
        printf("\n");
    return 1;
}

int shell_pwd()
{
    char *pwd;

    pwd = getenv("PWD");
    printf("%s\n", pwd);
    return 1;
}

int shell_export(char **tokens, t_data *data)
{
    int i;

    i = 0;
    if (!tokens[1])
    {
        get_allenv(data->env);
    }
    else
    {
        printf("test2 \n");
        data->env = ft_ptrjoin(tokens[1], data->env);
    }
    printf("test3 \n");
    return 1;
}

int launch_builtins(int id, char **tokens, t_data *data)
{
    int ret;

    ret = 0;
    if (id == 1)
        ret = shell_cd(tokens);
    else if (id == 2)
        ret = shell_echo(tokens);
    else if(id == 3)
        ret = shell_pwd();
    else if (id == 4)
        ret = shell_export(tokens, data);
    return ret;
}
