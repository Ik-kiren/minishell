/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daribeir <daribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:42:46 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/17 21:44:10 by daribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_utils3(int *count, char *token, int *i)
{
	*count += 1;
	while (token[*count] && !check_utils(token[*count]))
		*count += 1;
	*i += 1;
}

char	*replace_utils2(int *l)
{
	char	*ret;

	*l = 0;
	ret = malloc(sizeof(char) * 1);
	ret[0] = '\0';
	return (ret);
}

char	*malloc_replace(char *token, char *tmp, int *i, int count)
{
	free_ptr(tmp);
	while (token[*i] && ((token[*i] != '$') || (token[*i + 1] && token[*i] == '$' && token[*i + 1] == '$')))
		*i += 1;
	tmp = malloc(sizeof(char) * (*i - count + 1));
	return (tmp);
}

char	*replace_utils(t_data *data, char *token, int i, int count)
{
	char	*tmp;
	char	*ret;
	char	*str;
	int		l;

	ret = replace_utils2(&l);
	str = NULL;
	tmp = NULL;
	while (token[i])
	{
		tmp = malloc_replace(token, tmp, &i, count);
		while (count < i)
			tmp[l++] = token[count++];
		tmp[l] = '\0';
		l = 0;
		ret = ft_strjoin_f(ret, tmp);
		if (!token[i])
			break ;
		free_ptr(str);
		ret = ft_strjoin_f(ret, (str = search_env_var(data, token + i)));
		replace_utils3(&count, token, &i);
	}
	double_free(tmp, str);
	return (ret);
}

char	*replace_env_var(t_data *data, char *token)
{
	int		i;
	int		count;
	char	*ret;
	int		quotes;

	i = 0;
	count = 0;
	quotes = 0;
	ret = replace_utils(data, token, i, count);
	if (check_squotes(token))
		ret = erase_quotes(ret, quotes);
	return (ret);
}
