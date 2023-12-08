/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:41:10 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/08 14:25:30 by cdupuis          ###   ########.fr       */
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
	quotes_states2(line, i, &quotes, &dquotes);
	while (line[i])
	{
		l = 0;
		if (line[i] != '\0' && line[i] != ' ')
		{
			if (line[i] == '|' && (line[i + 1] != ' ' || line[i - 1] != ' ') && line[i + 1] != '\0')
			{
				tokens[j][l++] = line[i];
				tokens[j++][l] = '\0';
				if (line[i + 1] && line[i] == '|' && line[i + 1] == ' ')
					i++;
				l = 0;
				i++;
			}
			while (line[i] && (line[i] != ' ' || quotes || dquotes) && line[i] != '|')
			{
				quotes_states2(line, i, &quotes, &dquotes);
				tokens[j][l++] = line[i++];
			}
			tokens[j++][l] = '\0';
		}
		if (!line[i])
			break ;
		i++;
		if (i > 0 && line[i - 1] == '|')
				i--;
	}
	tokens[j] = NULL;
}

char	**get_tokens(char *line, char **tokens)
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
	get_tokens_utils(line, tokens, i, j);
	return (tokens);
}
