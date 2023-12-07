/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:08:28 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/06 15:19:19 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_op_quotes(char *token)
{
	int	quotes;
	int	i;

	quotes = 0;
	i = 0;
	while (token[i])
	{
		quotes_states(token, i, &quotes);
		i++;
	}
	if (quotes == 1 || quotes == 2)
		return (0);
	return (1);
}

int	quotes_states(char *token, int i, int *quotes)
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
	else if (token[i] == '\"' && *quotes == 0)
	{
		*quotes = 2;
		return (1);
	}
	else if (token[i] == '\"' && *quotes == 2)
	{
		*quotes = 0;
		return (1);
	}
	return (0);
}

char	*update_quotes(char *token, t_data *data, int quotes)
{
	int		i;

	i = 0;
	while (token[i])
	{
		quotes_states(token, i, &quotes);
		if (token[i] == '$' && quotes != 1)
		{
			return (replace_env_var(data, token));
		}
		i++;
	}
	return (erase_quotes(token, 0));
}

char	*replace_squotes(t_data *data, char *token)
{
	int		quotes;
	char	*tmp;

	quotes = 0;
	tmp = update_quotes(token, data, quotes);
	free_ptr(token);
	return (tmp);
}
