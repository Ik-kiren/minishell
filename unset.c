#include "minishell.h"

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