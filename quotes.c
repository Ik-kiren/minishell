/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:08:28 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/04 17:09:42 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	quotes_states(char *token, int i, int *squotes, int *dquotes)
{
	int	none;

	if (token[i] == '\'' && *squotes == 0)
	{
		none = 1;
		*squotes = 1;
	}
	else if (token[i] == '\'' && *squotes == 1)
		*squotes = 0;
	if (token[i] == '\"' && *dquotes == 0)
		*dquotes = 1;
	else if (token[i] == '\"' && *dquotes == 1)
	{
		none = 1;
		*dquotes = 0;
	}
	return (none);
	
	if (token[i] == '\'' && *squotes == 0)
	{
		none = 1;
		*squotes = 1;
	}
	else if (token[i] == '\'' && *squotes == 1)
		*squotes = 0;
	if (token[i] == '\"' && *dquotes == 0)
		*dquotes = 2;
	else if (token[i] == '\"' && *dquotes == 2)
	{
		none = 1;
		*dquotes = 0;
	}
}*/

int	quotes_states(char *token, int i, int *squotes, int *dquotes)
{
	int	none;

	if (token[i] == '\'' && *squotes == 0)
	{
		none = 1;
		*squotes = 1;
	}
	else if (token[i] == '\'' && *squotes == 1)
		*squotes = 0;
	if (token[i] == '\"' && *dquotes == 0)
		*dquotes = 1;
	else if (token[i] == '\"' && *dquotes == 1)
	{
		none = 1;
		*dquotes = 0;
	}
	return (none);
}

char	*update_quotes(char *token, t_data *data, int *squotes, int *dquotes)
{
	int	i;
	int	none;

	none = 0;
	i = 0;
	while (token[i])
	{
		none = quotes_states(token, i, squotes, dquotes);
		printf("dquotes = %d\n", *dquotes);
		if ((token[i] == '$' && *squotes == 0) && *dquotes == 0)
			return (replace_env_var(data, token));
		i++;
	}
	if (none == 0)
		return (replace_env_var(data, token));
	else
		token = erase_quotes(token);
	return (token);
}

char	*replace_squotes(t_data *data, char *token)
{
	int	squotes;
	int	dquotes;

	squotes = 0;
	dquotes = 1;
	token = update_quotes(token, data, &squotes, &dquotes);
	return (token);
}
