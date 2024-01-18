/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:41:10 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/18 10:42:35 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_tokens_utils3(char *line, int *i)
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

int	get_tokens_utils2(char *line, char *tokens, int *i, int *l)
{
	if (c_pr(line[*i]) && line[*i + 1] != '\0')
	{
		if (check_sp(line[*i + 1]) && !line[*i + 2])
		{
			*i += 1;
			while (check_sp(line[*i]))
				*i += 1;
			return (0);
		}
		if (!ft_strncmp(line + *i, "<<", 2) || !ft_strncmp(line + *i, ">>", 2))
		{
			tokens[*l] = line[*i];
			*l += 1;
			*i += 1;
		}
		tokens[*l] = line[*i];
		tokens[*l + 1] = '\0';
		if (line[*i + 1] && c_pr(line[*i]))
			*i += 1;
		*l = 0;
		while (check_sp(line[*i]))
			*i += 1;
		return (1);
	}
	return (0);
}

void	get_tokens_utils(char *line, char **tokens, int i, int j)
{
	int	l;
	int	q;
	int	dq;

	get_t_u(&q, &dq);
	while (line[i])
	{
		l = 0;
		if (line[i] != '\0' && !(check_sp(line[i])))
		{
			j += get_tokens_utils2(line, tokens[j], &i, &l);
			if (!line[i] || (c_pr(line[i]) && !line[i + 1]))
				break ;
			while (line[i] && (!(check_sp(line[i])) || \
				q || dq || c_pr(line[i])))
			{
				quotes_states2(line, i, &q, &dq);
				tokens[j][l++] = line[i++];
			}
			tokens[j++][l] = '\0';
		}
		if (!get_tokens_utils3(line, &i))
			break ;
	}
	tokens[j] = NULL;
}

char	**get_tokens(char *line, char **tokens)
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
	get_tokens_utils(line, tokens, i, j);
	return (tokens);
}
