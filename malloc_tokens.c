/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:40:22 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/05 15:57:11 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_tokens_utils2(char *line, int *i, int *count)
{
	*i += 1;
	while (line[*i] && line[*i] != '\"' && line[*i] != '\'')
	{
		*count += 1;
		*i += 1;
	}
	if (line[*i] == '\0')
	{
		*count += 1;
		return ;
	}
	*count += 2;
	*i += 1;
	if (line[*i] && line[*i + 1])
	*i += 1;
}

void	malloc_tokens_utils(char *line, char **tokens, int i, int j)
{
	int	count;
	int	quotes;
	int	dquotes;

	count = 0;
	quotes = 0;
	dquotes = 0;
	while (line[++i])
	{
		count = 0;
		quotes_states2(line, i, &quotes, &dquotes);
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
	}
	tokens[j] = NULL;
}

void	malloc_tokens(char *line, char **tokens)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (line[0] == ' ')
	{
		i++;
		while (line[i] == ' ')
			i++;
	}
	malloc_tokens_utils(line, tokens, i, j);
}
