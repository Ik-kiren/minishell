#include "minishell.h"

int token_size(char *token)
{
    int i;

    i = 0;
    while (token[i] != '=')
        i++;
    return i;
}

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

int ft_strncmp(char *s1, char *s2, int size)
{
    int i;

    i = 0;
    while (s1[i] && i <= size)
    {
        if (s1[i] != s2[i])
            return 0;
        i++;
    }
    return 1;
}

int shell_cd(char **tokens, t_data *data)
{
    int idx;
    char *tmp;
    char *pwd_tmp;

    idx = get_env_idx(data, "PWD=", 3);
    if (tokens[1] == NULL)
        fprintf(stderr, "pathname error");
    else
        if (chdir(tokens[1]) != 0)
          perror("lsh"); 
        else
        {
            tmp = ft_strjoin(data->env[idx], "/");
            pwd_tmp = ft_strjoin(tmp, tokens[1]);
            free(data->env[idx]);
            free(tmp);
            data->env[idx] = pwd_tmp;
        }
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

int shell_pwd(char **tokens,t_data *data)
{
    int idx;

    if (tokens[1] != NULL)
        return 0;
    idx = get_env_idx(data, "PWD=", 3);
    printf("%s\n", data->env[idx] + 4);
    return 1;
}

int get_env_idx(t_data *data, char *token, int key)
{
    int i;

    i = 0;
    while (data->env[i])
    {
        if (ft_strncmp(data->env[i], token, key))
            return i;
        i++;
    }
    return -1;
}

int shell_env(t_data *data, char **tokens)
{
    if (tokens[1] != NULL)
        return 0;
    get_allenv(data->env);
    return 1;
}

int shell_exit(t_data *data, char **tokens)
{
    if (tokens[1] != NULL)
        return 0;
    free_ptr(data->env);
    free_ptr(tokens);
    printf("exit\n");
    exit(EXIT_SUCCESS);
    return 1;
}

int launch_builtins(int id, char **tokens, t_data *data)
{
    int ret;

    ret = 0;
    if (id == 1)
        ret = shell_cd(tokens, data);
    else if (id == 2)
        ret = shell_echo(tokens);
    else if(id == 3)
        ret = shell_pwd(tokens, data);
    else if (id == 4)
        ret = shell_export(tokens, data);
    else if (id == 5)
        ret = shell_unset(tokens, data);
    else if (id == 6)
        ret = shell_env(data, tokens);
    else if (id == 7)
        ret = shell_exit(data, tokens);
    return ret;
}
