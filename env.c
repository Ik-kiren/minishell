/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:28:19 by cdupuis           #+#    #+#             */
/*   Updated: 2023/11/30 13:32:26 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_idx(t_data *data, char *token)
{
	int		i;
	size_t	len;

	i = 0;
	while (data->env[i])
	{
		len = 0;
		while (data->env[i][len] != '=' && data->env[i][len] != '\0')
			len++;
		if (len <= ft_strlen(token) && token[len] == '\0')
			len--;
		if (ft_strncmp(data->env[i], token, len))
			return (i);
		i++;
	}
	return (-1);
}

char	*get_env_var(t_data *data, char *token)
{
	char	*tmp;
	int		idx;

	if (token[0] == '?' && !token[1])
		return (ft_strdup(data->ret));
	idx = get_env_idx(data, token);
	if (idx == -1)
		return (NULL);
	tmp = ft_strdup(data->env[idx]);
	return (tmp);
}

int	shell_env(t_data *data)
{
	char	*error;

	if (data->cmd->args[1] != NULL)
	{
		error = ft_strjoin("env: ", data->cmd->args[1]);
		errno = ENOENT;
		perror(error);
		return (1);
	}
	get_allenv(data->env);
	return (1);
}

int	shell_pwd(char **tokens, t_data *data)
{
	int	idx;

	if (tokens[1] != NULL)
		return (0);
	idx = get_env_idx(data, "PWD");
	printf("%s\n", data->env[idx] + 4);
	return (1);
}
