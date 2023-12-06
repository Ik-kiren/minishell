/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:51:05 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/06 11:10:39 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_realloc(t_data *data, char *token)
{
	char	**tmp;
	int		len;
	int		i;

	len = ft_ptrlen(data->env);
	tmp = (char **)malloc(sizeof(char *) * (len + 2));
	if (!tmp)
		return (NULL);
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
	return (tmp);
}

int	set_env_variable(t_data *data, char *token)
{
	int	idx;

	idx = get_env_idx(data, token);
	if (idx != -1)
	{
		free(data->env[idx]);
		data->env[idx] = ft_strdup(token);
	}
	else
		data->env = env_realloc(data, token);
	return (1);
}

int	shell_export(char **tokens, t_data *data)
{
	int	j;

	j = 1;
	if (!data->cmd->args[1])
		get_allenv(data->env, "declare -x ");
	else
	{
		while (tokens[j])
		{
			if (!check_export(tokens[j]))
				return (1);
			set_env_variable(data, tokens[j]);
			j++;
		}
	}
	return (1);
}
