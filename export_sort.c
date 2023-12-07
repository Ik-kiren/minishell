/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:15:00 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/07 13:24:39 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_export_swap(char	**str1, char	**str2)
{
	char	*tmp;

	tmp = ft_strdup(*str1);
	free_ptr(*str1);
	*str1 = ft_strdup(*str2);
	free_ptr(*str2);
	*str2 = ft_strdup(tmp);
	free_ptr(tmp);
}

void	sort_export(char **envp, int len)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			while (envp[j][k] && envp[j + 1][k]
					&& (envp[j][k] == envp[j + 1][k]))
				k++;
			if (envp[j][k] > envp[j + 1][k])
			{
				sort_export_swap(&envp[j], &envp[j + 1]);
			}
			j++;
			k = 0;
		}
		i++;
	}
}

void	get_sort_exp(char **envp)
{
	char	**tmp_envp;
	int		i;
	size_t	len;

	i = 0;
	len = ft_ptrlen(envp);
	tmp_envp = malloc(sizeof(char *) * (len + 1));
	while (envp[i] != NULL)
	{
		tmp_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	tmp_envp[i] = NULL;
	sort_export(tmp_envp, len);
	i = 0;
	while (tmp_envp[i])
	{
		printf("declare -x %s\n", tmp_envp[i]);
		i++;
	}
	free_str(tmp_envp);
}
