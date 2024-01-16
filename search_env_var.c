/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:42:34 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/16 15:53:04 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*s_e_v_utils(char *token, size_t *i)
{
	char	*tmp;

	while (token[*i] && token[*i] != '\"' && !(check_sp(token[*i]))
		&& token[*i] != '\'')
		*i += 1;
	tmp = malloc(sizeof(char) * (*i + 1));
	*i = 0;
	while (token[*i] && token[*i] != '\"' && !(check_sp(token[*i]))
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
	int		dolars;
	size_t	i;

	i = 0;
	dolars = 0;
	tmp = s_e_v_utils(token, &i);

	str = get_env_var(data, tmp + 1, &dolars);
	if (!str)
	{
		str = malloc(sizeof(char) * 1);
		str[0] = '\0';
	}
	else if (!(dolars))
		str = get_key_value(str);
	free_ptr(tmp);
	return (str);
}
