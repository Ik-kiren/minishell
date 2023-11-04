#include "minishell.h"

void ft_strcopy(char *dst, char *src)
{
    int i;

    i = 0;
    while (src[i])
    {
        dst[i] = src[i];
        i++;
    }
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

int unset_env_variable(t_data *data, char *token)
{
    int idx;
    char *token_tmp;

    token_tmp = ft_strjoin(token, "=");
    idx = get_env_idx(data, token_tmp);
    printf("unset_idx = %d\n", idx);
    if (idx == -1)
        return 0;
    else
    {
        data->env = env_unset_realloc(data, idx);
    }
    free(token_tmp);
    return 1;
}

int shell_unset(char **tokens, t_data *data)
{
    if (tokens[1] == NULL)
        return 0;
    unset_env_variable(data, tokens[1]);
    return 1;
}