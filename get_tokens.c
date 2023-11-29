/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:41:10 by cdupuis           #+#    #+#             */
/*   Updated: 2023/11/29 15:12:11 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_tokens_utils(char *line, char **tokens, int i, int j)
{
	int	l;

	while (line[++i])
	{
		l = 0;
		if (line[i] == '\"' || line[i] == '\'')
		{
			tokens[j][l++] = line[i++];
			while (line[i] != '\"' && line[i] != '\'')
			{
				tokens[j][l++] = line[i++];
			}
			tokens[j][l++] = line[i];
			tokens[j++][l] = '\0';
		}
		else if (line[i] != '\0' && line[i] != ' ')
		{
			while (line[i] != '\0' && line[i] != ' ')
				tokens[j][l++] = line[i++];
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
	get_tokens_utils(line, tokens, i, j);
	return (tokens);
}
