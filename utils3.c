/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:12:37 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/06 18:07:18 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_states2(char *token, int i, int *quotes, int *dquotes)
{
	if (token[i] == '\'' && *quotes == 0)
	{
		*quotes = 1;
		return (1);
	}
	else if (token[i] == '\'' && *quotes == 1)
	{
		*quotes = 0;
		return (1);
	}
	else if (token[i] == '\"' && *dquotes == 0)
	{
		*dquotes = 2;
		return (1);
	}
	else if (token[i] == '\"' && *dquotes == 2)
	{
		*dquotes = 0;
		return (1);
	}
	return (0);
}

int	check_utils(char c)
{
	if (c == '$' || check_spchar(c))
	{
		return (1);
	}
	return (0);
}

int	check_spchar(char c)
{
	if ((c >= 33 && c <= 47) || (c >= 58 && c <= 64)
		|| (c >= 91 && c <= 94) || (c >= 123 && c <= 126) || c == 96)
		return (1);
	return (0);
}

int	check_export(char *str)
{
	int	i;
	int	equal;

	i = 0;
	equal = 0;
	while (str[i])
	{
		if (str[i] == '=')
			equal = 1;
		else if (check_spchar(str[i]))
		{
			printf("export: %s: not a valid identifier\n", str);
			return (0);
		}
		i++;
	}
	if (!equal)
		return (0);
	return (1);
}

int	count_quotes(char *line, int i, int count)
{
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			count++;
			i++;
			while (line[i] && line[i] != '\"' && line[i] != '\'')
			{
				if (line[i] == '\0')
					return (0);
				i++;
			}
			if (line[i] == '\0')
				break ;
		}
		if (line[i] == ' ' && line[i + 1] != ' '
			&& line[i + 1] != '\0' && line[i + 1] != '\"'
			&& line[i + 1] != '\'')
			count++;
		i++;
	}
	return (count);
}
