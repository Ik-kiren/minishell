/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:40:22 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/08 14:24:58 by cdupuis          ###   ########.fr       */
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
			printf("c = %c\n", line[i]);
			if (line[i + 1] && line[i] == '|' && (line[i + 1] != ' ' || line[i - 1] != ' '))
			{
				tokens[j++] = malloc(sizeof(char) * 2);
				if (line[i + 1] && line[i] == '|' && line[i + 1] == ' ')
					i++;
				i++;
			}
			printf("c2 = %c\n", line[i]);
			while (line[i] && (line[i] != ' ' || quotes || dquotes) && line[i] != '|')
			{
				quotes_states2(line, i, &quotes, &dquotes);
				i++;
				count++;
			}
			tokens[j++] = malloc(sizeof(char) * (count + 1));
		}
		printf("c1 = %c\n", line[i]);
		if (!line[i])
			break ;
		i++;
		if (i > 0 && line[i - 1] == '|')
				i--;
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
