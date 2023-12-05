/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:42:34 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/05 15:15:17 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	malloc_quotes(char *token)
{
	int	i;
	int	quotes;
	int	count;

	count = 0;
	quotes = 0;
	i = 0;
	while (token[i])
	{
		while (quotes_states(token, i, &quotes) == 1)
			i++;
		if (token[i])
		{
			while (token[i] == ' ' && token[i + 1] == ' ')
				i++;
			count++;
		}
		if (!token[i])
			return (count);
		if (quotes_states(token, i, &quotes) != 1)
			i++;
	}
	return (count);
}

char	*erase_quotes(char *token, int quotes)
{
	char	*tmp;
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = malloc_quotes(token);
	tmp = malloc(sizeof(char) * (count + 1));
	while (token[i])
	{
		while (quotes_states(token, i, &quotes) == 1)
			i++;
		if (token[i])
		{
			while (token[i] == ' ' && token[i + 1] == ' ')
				i++;
			tmp[j++] = token[i];
		}
		if (!token[i])
			break ;
		if (quotes_states(token, i, &quotes) != 1)
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
	while (token[i] && token[i] != '\"' && token[i] != ' ' && token[i] != '\'')
		i++;
	tmp = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (token[i] && token[i] != '\"' && token[i] != ' ' && token[i] != '\'')
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

int	check_squotes(char *token)
{
	int	i;

	i = -1;
	while (token[++i])
	{
		if (token[i] == '\"' || token[i] == '\'')
			return (1);
	}
	return (0);
}
