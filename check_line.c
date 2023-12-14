/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 09:54:26 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/14 10:37:36 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_p_line(char *line, int *i, int q)
{
	int k;

	k = 0;
	while (line[*i] == '|')
	{
		*i += 1;
		if (!q)
			k++;
	}
	if (k >= 2)
		return (0);
	return (1);
}

int check_r_line(char *line, int *i, int q)
{
	int k;

	k = 0;
	while (line[*i] == '<' || line[*i] == '>')
	{
		*i += 1;
		if (!q)
			k++;
	}
	if (k >= 3)
		return (0);
	return (1);
}

int	check_line(char *line)
{
    int	i;
	int	q;
	
	i = 0;
	q = 0;
	if (!check_op_quotes(line))
		return (print_error("error: unclosed quotes"));
	while (line[i])
	{
		quotes_states(line, i, &q);
		if (line[i] == '|')
			if (!check_p_line(line, &i, q))
				return (print_error("error: format"));
		if (line[i] == '<' || line[i] == '>')
			if (!check_r_line(line, &i, q))
				return (print_error("error: format"));
		i++;
	}
	return (1);
}