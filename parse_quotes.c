/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:42:34 by cdupuis           #+#    #+#             */
/*   Updated: 2023/11/30 13:48:13 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*erase_quotes(char *token)
{
	char	*tmp;
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = 0;
	while (token[i])
	{
		if (token[i] != '\"' && token[i] != '\'')
			count++;
		i++;
	}
	tmp = malloc(sizeof(char) * (count + 1));
	i = 0;
	while (token[i])
	{
		if (token[i] != '\"' && token[i] != '\'')
			tmp[j++] = token[i];
		i++;
	}
	tmp[j] = '\0';
	free(token);
	return (tmp);
}

char	*search_env_var(t_data	*data, char	*token)
{
	char	*tmp;
	char	*str;
	size_t	i;

	i = 0;
	while (token[i] && token[i] != '\"' && token[i] != ' ')
		i++;
	tmp = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (token[i] && token[i] != '\"' && token[i] != ' ')
	{
		tmp[i] = token[i];
		i++;
	}
	tmp[i] = '\0';
	str = get_env_var(data, tmp + 1);
	if (!str)
	{
		str = malloc(sizeof(char) * 1);
		str[0] = '\0';
	}
	else
		str = get_key_value(str);
	free_ptr(tmp);
	return (str);
}

int	check_squotes(char *token, int squotes, int dquotes)
{
	int	i;

	i = -1;
	while (token[++i])
	{
		if (token[i] == '\'' && squotes == 0)
		{
			squotes = 1;
		}
		else if (token[i] == '\'' && squotes == 1)
			squotes = 0;
		if (token[i] == '\"' && dquotes == 0)
			dquotes = 1;
		else if (token[i] == '\"' && dquotes == 1)
			dquotes = 0;
	}
	if (squotes == 1 || dquotes == 0)
		return (0);
	printf("");
	return (1);
}
