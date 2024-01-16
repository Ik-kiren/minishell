/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:28:19 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/16 12:46:00 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			tokens[i] = erase_quotes(tokens[i], quotes);
		i++;
	}
	return (1);
}
