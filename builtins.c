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

char **env_realloc(t_data *data, char *token)
{
    char **tmp;
    int len;
    int i;

    len = ft_ptrlen(data->env);
    tmp = (char **)malloc(sizeof(char *) * (len + 2));
    if (!tmp)
        return NULL;
    i = 0;
    while (data->env[i])
    {
        tmp[i] = ft_strdup(data->env[i]);
        free(data->env[i]);
        i++;
    }
    tmp[i] = ft_strdup(token);
    tmp[i + 1] = NULL;
    free(data->env);
    return tmp;
}

char **env_unset_realloc(t_data *data, int idx)
{
    char **tmp;
    int len;
    int i;
    int j;

    len = ft_ptrlen(data->env);
    tmp = (char **)malloc(sizeof(char *) * len);
    if (!tmp)
        return NULL;
    i = 0;
    j = 0;
    while (data->env[j])
    {
        tmp[i] = ft_strdup(data->env[j]);
        free(data->env[j++]);
        i++;
        if (j == idx)
            j++;
    }
    tmp[i] = NULL;
    free(data->env);
    return tmp;
}

int set_env_variable(t_data *data, char *token, int key)
{
    int idx;

    idx = get_env_idx(data, token, key);
    if (idx != -1)
    {
        free(data->env[idx]);
        data->env[idx] = ft_strdup(token);
    }
    else
        data->env = env_realloc(data, token);
    return 1;
}

int shell_export(char **tokens, t_data *data)
{
    int i;

    i = 0;
    if (!tokens[1])
        get_allenv(data->env);
    else
    {
        while (tokens[1][i] != '=')
            i++;
        set_env_variable(data, tokens[1], i);
    }
    return 1;
}

int unset_env_variable(t_data *data, char *token, int key)
{
    int idx;

    printf("unset_key = %d\n", key);
    idx = get_env_idx(data, token, key);
    printf("unset_idx = %d\n", idx);
    if (idx == -1)
        return 0;
    else
    {
        data->env = env_unset_realloc(data, idx);
    }
    return 1;
}

int shell_unset(char **tokens, t_data *data)
{
    int len;

    len = ft_strlen(tokens[1]);
    unset_env_variable(data, tokens[1], len - 1);
    return 1;
}

int shell_env(t_data *data)
{
    get_allenv(data->env);
    return 1;
}

int shell_exit(t_data *data, char **tokens)
{
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
        ret = shell_cd(tokens);
    else if (id == 2)
        ret = shell_echo(tokens);
    else if(id == 3)
        ret = shell_pwd();
    else if (id == 4)
        ret = shell_export(tokens, data);
    else if (id == 5)
        ret = shell_unset(tokens, data);
    else if (id == 6)
        ret = shell_env(data);
    else if (id == 7)
        ret = shell_exit(data, tokens);
    return ret;
}
