/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:42:46 by cdupuis           #+#    #+#             */
/*   Updated: 2023/11/29 15:30:26 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_free(void *ptr1, void *ptr2)
{
	free_ptr(ptr1);
	free_ptr(ptr2);
}

char	*replace_utils2(char **token, int *l)
{
	char	*ret;

	*l = 0;
	ret = malloc(sizeof(char) * 1);
	ret[0] = '\0';
	*token = erase_quotes(*token);
	return (ret);
}

char	*replace_utils(t_data *data, char *token, int i, int count)
{
	char	*tmp;
	char	*ret;
	char	*str;
	int		l;

	ret = replace_utils2(&token, &l);
	while (token[i])
	{
		while (token[i] && token[i] != '$')
			i++;
		tmp = malloc(sizeof(char) * (i + 1));
		while (count < i)
			tmp[l++] = token[count++];
		tmp[l] = '\0';
		l = 0;
		ret = ft_strjoin_f(ret, tmp);
		if (!token[i])
			break ;
		str = search_env_var(data, token + i);
		ret = ft_strjoin_f(ret, str);
		while (token[i] && token[i++] != ' ')
			count++;
	}
	double_free(tmp, str);
	return (ret);
}

char	*replace_env_var(t_data *data, char *token)
{
	int		i;
	int		count;
	char	*ret;

	i = 0;
	count = 0;
	ret = replace_utils(data, token, i, count);
	return (ret);
}
