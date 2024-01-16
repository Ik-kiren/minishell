/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:42:34 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/16 18:30:42 by cdupuis          ###   ########.fr       */
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
	while (token && token[i])
	{
		while (quotes_states(token, i, &quotes) == 1)
			i++;
		if (token[i])
		{
			while (check_sp(token[i]) && quotes_states(token, i, &quotes))
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

void	erase_quotes_utils(int *i, int *j, int *count, char *token)
{
	*i = 0;
	*j = 0;
	*count = malloc_quotes(token);
}

char	*erase_quotes(char *token, int quotes)
{
	char	*tmp;
	int		i;
	int		j;
	int		count;

	erase_quotes_utils(&i, &j, &count, token);
	tmp = malloc(sizeof(char) * (count + 1));
	while (token[i])
	{
		while (quotes_states(token, i, &quotes) == 1)
			i++;
		if (token[i])
		{
			while (token[i] && quotes_states(token, i, &quotes))
				i++;
			tmp[j++] = token[i];
		}
		if (!token[i])
			break ;
		if (quotes_states(token, i, &quotes) != 1)
			i++;
	}
	tmp[j] = '\0';
	free_ptr(token);
	return (tmp);
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
