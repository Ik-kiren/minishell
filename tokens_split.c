/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:50:47 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/15 12:02:05 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_c_t(int *count, int *quotes, int *dquotes)
{
	*count = 0;
	*dquotes = 0;
	*quotes = 0;
}

static void	add_space_after_i(char **line, int i)
{
	int		len;
	char	*ret;
	int		j;

	len = ft_strlen(*line);
	ret = malloc(sizeof(char) * (len + 2));
	j = -1;
	while (++j <= i)
		ret[j] = (*line)[j];
	ret[j] = ' ';
	while (++j < len)
		ret[j] = (*line)[j - 1];
	ret[j] = (*line)[j - 1];
	ret[len + 1] = '\0';
	free_ptr(*line);
	*line = ret;
}

void	count_t2(char **line, int *i, int *count)
{
	if (c_pr((*line)[*i])  && (*line)[*i + 1] != ' ' && (*line)[*i + 1] != '\0')
	{
		if (c_pr((*line)[*i + 1]))
		{
			*count += 1;
			*i += 2;
			add_space_after_i(line, *i - 1);
			*i += 1;
		}
		else
		{
			*count += 1;
			add_space_after_i(line, *i - 1);
			*i += 1;
			add_space_after_i(line, *i);
			*i += 1;
		}
	}
	if (c_pr((*line)[*i + 1]) && (*line)[*i] != ' ')
	{
		*count += 1;
		add_space_after_i(line, *i);
		*i += 1;
	}
}

int	count_tokens(char **line)
{
	int	i;
	int	count;
	int	quotes;
	int	dquotes;

	init_c_t(&count, &quotes, &dquotes);
	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] != '\0' && (*line)[i] != ' ')
		{
			count++;
			while ((*line)[i] && ((*line)[i] != ' ' || quotes || dquotes))
			{
				count_t2(line, &i, &count);
				quotes_states2(*line, i, &quotes, &dquotes);
				i++;
			}
		}
		if (!(*line)[i])
			break ;
		i++;
	}
	return (count);
}

char	**shell_split_tokens(t_data *data, char *line)
{
	char	**tokens;
	int		nbr_tokens;

	if (line[0] == '\0')
		return (NULL);
	if (!check_line(line))
		return (free_ptr(line));
	nbr_tokens = count_tokens(&line);
	if (nbr_tokens == 0)
		return (NULL);
	tokens = malloc(sizeof(char *) * (nbr_tokens + 1));
	if (!tokens)
	{
		free_ptr(line);
		return (NULL);
	}
	malloc_tokens(line, tokens);
	get_tokens(line, tokens);
	if (parse_env_var(data, tokens) == 0)
		return (NULL);
	free_ptr(line);
	return (tokens);
}
