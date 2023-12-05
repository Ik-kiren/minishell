/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:12:37 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/05 15:26:01 by cdupuis          ###   ########.fr       */
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
	if (c == '$' || ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
	{
		return (1);
	}
	return (0);
}
