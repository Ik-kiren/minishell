/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:41:10 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/05 15:57:26 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_tokens_utils(char *line, char **tokens, int i, int j)
{
	int	l;
	int	quotes;
	int	dquotes;

	quotes = 0;
	dquotes = 0;
	while (line[++i])
	{
		l = 0;
		quotes_states2(line, i, &quotes, &dquotes);
		if (line[i] != '\0' && line[i] != ' ')
		{
			while (line[i] && (line[i] != ' ' || quotes || dquotes))
			{
				quotes_states2(line, i, &quotes, &dquotes);
				tokens[j][l++] = line[i++];
			}
			tokens[j++][l] = '\0';
		}
		if (!line[i])
			break ;
	}
	tokens[j] = NULL;
}

char	**get_tokens(char *line, char **tokens)
{
	int	i;
	int	j;
	int	l;
	int	status;

	i = -1;
	j = 0;
	l = 0;
	status = 0;
	if (line[0] == ' ')
	{
		i++;
		while (line[i] == ' ')
			i++;
	}
	get_tokens_utils(line, tokens, i, j);
	return (tokens);
}
