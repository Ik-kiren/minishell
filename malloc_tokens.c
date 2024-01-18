/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: n43 <n43@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:40:22 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/18 16:33:09 by n43              ###   ########.fr       */
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
	while (check_sp(line[*i]))
		*i += 1;
	return (1);
}

void	malloc_tokens_utils3(char *line, char **tokens, int *i, int *j)
{
	int	count;

	count = 2;
	if (line[*i + 1] && c_pr(line[*i]))
	{
		if (check_sp(line[*i + 1]) && !line[*i + 2])
		{
			*i += 1;
			while (check_sp(line[*i]))
				*i += 1;
			return ;
		}
		if (!ft_strncmp(line + *i, "<<", 2) || !ft_strncmp(line + *i, ">>", 2))
		{
			*i += 1;
			count++;
		}
		tokens[*j] = malloc(sizeof(char) * count);
		if (line[*i + 1] && c_pr(line[*i]))
			*i += 1;
		*j += 1;
		while (check_sp(line[*i]))
			*i += 1;
	}
}

void	malloc_tokens_utils2(int *q, int *dq, int *count)
{
	*q = 0;
	*dq = 0;
	*count = 0;
}

void	malloc_tokens_utils(char *l, char **tokens, int i, int j)
{
	int	count;
	int	q;
	int	dq;

	malloc_tokens_utils2(&q, &dq, &count);
	while (l[i])
	{
		count = 0;
		if (l[i] != '\0' && !(check_sp(l[i])))
		{
			malloc_tokens_utils3(l, tokens, &i, &j);
			if (!l[i] || (c_pr(l[i]) && !l[i + 1]))
				break ;
			while (l[i] && (!(check_sp(l[i])) || q || dq || c_pr(l[i])))
			{
				quotes_states2(l, i, &q, &dq);
				i++;
				count++;
			}
			tokens[j++] = malloc(sizeof(char) * (count + 1));
		}
		if (!malloc_tokens_utils4(l, &i))
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
	if (check_sp(line[0]))
	{
		i++;
		while (check_sp(line[i]))
			i++;
	}
	malloc_tokens_utils(line, tokens, i, j);
}
