/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:42:34 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/08 11:21:01 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*s_e_v_utils(char *token, size_t *i)
{
	char	*tmp;

	while (token[*i] && token[*i] != '\"' && token[*i] != ' '
		&& token[*i] != '\'')
		*i += 1;
	tmp = malloc(sizeof(char) * (*i + 1));
	*i = 0;
	while (token[*i] && token[*i] != '\"' && token[*i] != ' '
		&& token[*i] != '\'')
	{
		tmp[*i] = token[*i];
		*i += 1;
	}
	tmp[*i] = '\0';
	return (tmp);
}

char	*search_env_var(t_data	*data, char	*token)
{
	char	*tmp;
	char	*str;
	size_t	i;

	i = 0;
	tmp = s_e_v_utils(token, &i);
	if (tmp[1] == '?' && !tmp[2])
	{
		free(tmp);
		return (ft_itoa(data->ret));
	}
	str = get_env_var(data, tmp + 1);
	if (!str)
	{
		str = malloc(sizeof(char) * 1);
		str[0] = '\0';
	}
	else
		str = get_key_value(str);
	free_ptr(tmp);
	return (str);
}
