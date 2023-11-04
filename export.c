#include "minishell.h"

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

int set_env_variable(t_data *data, char *token)
{
    int idx;

    idx = get_env_idx(data, token);
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
    int j;

    j = 1;
    if (!tokens[1])
            get_allenv(data->env);
    else
    {
        while (tokens[j])
        {
            set_env_variable(data, tokens[j]);
            j++;
        }
    }
    return 1;
}