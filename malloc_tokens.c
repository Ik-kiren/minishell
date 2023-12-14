/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:40:22 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/14 10:33:52 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	malloc_tokens_utils4(char *line, int *i)
{
	if (!line[*i])
		return (0);
	*i += 1;
	if (*i > 0 && c_pr(line[*i - 1]))
		*i -= 1;
	while (line[*i] == ' ')
		*i += 1;
	return (1);
}

void	malloc_tokens_utils3(char *line, char **tokens, int *i, int *j)
{
	int	count;

	count = 2;
	if (line[*i + 1] && c_pr(line[*i]))
	{
		if (line[*i + 1] == ' ' && !line[*i + 2])
		{
			*i += 1;
			while (line[*i] == ' ')
				*i += 1;
			return ;
		}
		if (!ft_strncmp(line + *i, "<<", 2) || !ft_strncmp(line + *i, ">>", 2))
		{
			*i += 1;
			count++;
		}
		tokens[*j] = malloc(sizeof(char) * count);
		if (line[*i + 1] && c_pr(line[*i]) && line[*i + 1] == ' ')
			*i += 1;
		*j += 1;
		while (line[*i] == ' ')
			*i += 1;
	}
}

void	malloc_tokens_utils2(int *q, int *dq, int *count)
{
	*q = 0;
	*dq = 0;
	*count = 0;
}

void	malloc_tokens_utils(char *line, char **tokens, int i, int j)
{
	int	count;
	int	q;
	int	dq;

	malloc_tokens_utils2(&q, &dq, &count);
	while (line[i])
	{
		count = 0;
		if (line[i] != '\0' && line[i] != ' ')
		{
			malloc_tokens_utils3(line, tokens, &i, &j);
			if (!line[i] || (c_pr(line[i]) && !line[i + 1]))
				break ;
			while (line[i] && (line[i] != ' ' || q || dq || c_pr(line[i])))
			{
				quotes_states2(line, i, &q, &dq);
				i++;
				count++;
			}
			tokens[j++] = malloc(sizeof(char) * (count + 1));
		}
		if (!malloc_tokens_utils4(line, &i))
			break ;
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
