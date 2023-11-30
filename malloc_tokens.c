/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:40:22 by cdupuis           #+#    #+#             */
/*   Updated: 2023/11/30 14:49:00 by cdupuis          ###   ########.fr       */
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

	count = 0;
	while (line[++i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			malloc_tokens_utils2(line, &i, &count);
			tokens[j++] = malloc(sizeof(char) * (count + 1));
			count = 0;
			if (line[i] == '\0')
				break ;
		}
		if (line[i] != ' ')
			count++;
		if ((line[i] == ' ' && line[i - 1] != ' ')
			|| (line[i] != ' ' && line[i + 1] == '\0'))
		{
			tokens[j] = malloc(sizeof(char) * (count + 1));
			if (!tokens[j])
				tokens[j] = NULL;
			count = 0;
			j++;
		}
	}
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
		while (line[i + 1] == ' ')
			i++;
	}
	malloc_tokens_utils(line, tokens, i, j);
}
