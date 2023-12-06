/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:40:22 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/06 15:04:20 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_tokens_utils2(int *quotes, int *dquotes, int *count)
{
	*quotes = 0;
	*dquotes = 0;
	*count = 0;
}

void	malloc_tokens_utils(char *line, char **tokens, int i, int j)
{
	int	count;
	int	quotes;
	int	dquotes;

	malloc_tokens_utils2(&quotes, &dquotes, &count);
	quotes_states2(line, i, &quotes, &dquotes);
	while (line[i])
	{
		count = 0;
		if (line[i] != '\0' && line[i] != ' ')
		{
			while (line[i] && (line[i] != ' ' || quotes || dquotes))
			{
				quotes_states2(line, i, &quotes, &dquotes);
				i++;
				count++;
			}
			tokens[j++] = malloc(sizeof(char) * (count + 1));
		}
		if (!line[i])
			break ;
		i++;
	}
	tokens[j] = NULL;
}

void	malloc_tokens(char *line, char **tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (line[0] == ' ')
	{
		i++;
		while (line[i] == ' ')
			i++;
	}
	malloc_tokens_utils(line, tokens, i, j);
}
