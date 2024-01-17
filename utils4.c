/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daribeir <daribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:12:37 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/17 21:41:38 by daribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	c_pr(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	check_sp(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	else
		return (0);
}

void	unlink_doc(t_cmd *last)
{
	if (last->fdh && last->fdh->type == 3)
	{
		close(last->fdh->fd);
		unlink(last->fdh->name);
	}
}

char	**ft_realloc(char **tab1, char *s1)
{
	char	**ret;
	int		i;
	int		j;

	j = 0;
	i = ft_ptrlen(tab1) + 2;
	ret = malloc(sizeof(char *) * i);
	while (j < i - 2)
	{
		ret[j] = strdup(tab1[j]);
		j++;
	}
	ret[j] = s1;
	j++;
	ret[j] = '\0';
	free_str(tab1);
	return (ret);
}

void	get_allenv(char **envp, char *str)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (str)
			printf("%s", str);
		printf("%s\n", envp[i]);
		i++;
	}
}
