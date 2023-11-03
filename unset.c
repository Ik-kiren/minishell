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

int unset_env_variable(t_data *data, char *token, int key)
{
    int idx;
    char *token_tmp;
    int len;

    len = ft_strlen(token);
    token_tmp = malloc(sizeof(char) * (len + 2));
    ft_strcopy(token_tmp, token);
    token_tmp[len] = '=';
    token_tmp[len + 1] = '\0';
    printf("unset_key = %d\n", key);
    printf("unset_tmp = %s\n", token_tmp);
    idx = get_env_idx(data, token_tmp, key);
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
    int len;

    if (tokens[1] == NULL)
        return 0;
    len = ft_strlen(tokens[1]);
    unset_env_variable(data, tokens[1], len);
    return 1;
}