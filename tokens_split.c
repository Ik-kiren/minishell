/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:50:47 by cdupuis           #+#    #+#             */
/*   Updated: 2023/11/06 11:05:41 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (line[0] != ' ')
		count++;
	while (line[i])
	{
		if (line[i] == ' ' && line[i + 1] != ' ' && line[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

char	**malloc_tokens(char *line, char **tokens)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			count++;
		if ((line[i] == ' ' && line[i - 1] != ' ') || (line[i] != ' ' && line[i + 1] == '\0'))
		{
			printf("count_w = %d\n", count);
			tokens[j] = malloc(sizeof(char) * (count + 1));
			if (!tokens[j])
				return NULL;
			count = 0;
			j++;
		}
		i++;
	}
	return (tokens);
}

char	**get_tokens(char *line, char **tokens)
{
	int	i;
	int	j;
	int	l;

	i = 0;
	j = 0;
	l = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\0')
		{
			tokens[j][l++] = line[i];
		}
		if (line[i] != ' ' && line[i + 1] == '\0')
		{
			tokens[j][l] = '\0';
		}
		if ((line[i] == ' ' || line[i] == '\0') && line[i - 1] != ' ')
		{
			tokens[j][l] = '\0';
			l = 0;
			j++;
		}
		i++;
	}
	tokens[j + 1] = NULL;
	return (tokens);
}

char	**shell_split_tokens(char *line)
{
	char	**tokens;
	int		nbr_tokens;
	int		i;

	i = 0;
	if (line == NULL)
		exit(EXIT_SUCCESS);
	if (line[0] == '\0')
		return (NULL);
	nbr_tokens = count_tokens(line);
	printf("count = %d\n", nbr_tokens);
	tokens = malloc(sizeof(char *) * (nbr_tokens + 1));
	if (!tokens)
		return (NULL);
	malloc_tokens(line, tokens);
	get_tokens(line, tokens);
	while (i < nbr_tokens)
		printf("tokens = %s\n", tokens[i++]);
	return (tokens);
}
