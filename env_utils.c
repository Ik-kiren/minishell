/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:28:19 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/19 11:58:52 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

char	*erase_env_var(char *token)
{
	int		i;
	char	*tmp;

	i = 0;
	if (token[0] == '$')
		return (" ");
	while (token[i] != '$')
		i++;
	tmp = malloc(sizeof(char) * i);
	i = 0;
	while (token[i] != '$')
	{
		tmp[i] = token[i];
		i++;
	}
	tmp[i] = '\0';
	free(token);
	return (tmp);
}

int	parse_env_var(t_data *data, char **tokens)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (tokens[i])
	{
		if (ft_strchr('$', tokens[i]))
			tokens[i] = replace_squotes(data, tokens[i]);
		else if (check_squotes(tokens[i]))
		{
			tokens[i] = erase_quotes(tokens[i], quotes);
		}
		i++;
	}
	return (1);
}

int	shell_env(t_data *data)
{
	if (data->cmd->args[1] != NULL)
	{
		return (1);
	}
	get_allenv(data->env, NULL);
	return (1);
}

int	shell_pwd(t_data *data)
{
	int		idx;
	char	cwd[4096];

	idx = get_env_idx(data, "PWD");
	if (idx == -1)
	{
		printf("%s\n", getcwd(cwd, 4096));
		return (1);
	}
	printf("%s\n", data->env[idx] + 4);
	return (1);
}
