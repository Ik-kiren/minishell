/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:51:03 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/18 17:22:34 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_lcwd(char *str)
{
	char	*tmp;
	int		m_len;
	int		i;
	int		j;

	m_len = ft_strlen(str);
	i = m_len;
	j = 0;
	while (str[i] != '/' && i != 0)
		i--;
	tmp = malloc(sizeof(char) * (m_len - i + 1));
	if (!tmp)
		return (NULL);
	while (str[i])
	{
		tmp[j] = str[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*get_key_value(char *key)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (key[i] != '=')
		i++;
	i++;
	tmp = malloc(sizeof(char) * (ft_strlen(key) - i + 1));
	if (!tmp)
		return (NULL);
	while (key[i])
	{
		tmp[j] = key[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	free(key);
	return (tmp);
}

int	ft_strcmpargs(char *s1, char **s2)
{
	int	i;
	int	j;
	int	found;

	j = 0;
	while (j <= 6)
	{
		i = 0 ;
		found = 1;
		while (s1[i])
		{
			if (s1[i] != s2[j][i])
			{
				found = 0;
				break ;
			}
			i++;
		}
		if (found == 1)
		{
			return (j + 1);
		}
		j++;
	}
	return (0);
}

void	init_data(t_data *data, char **envp)
{
	int	len;
	int	i;

	i = 0;
	len = ft_ptrlen(envp);
	data->env = malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		data->env[i] = ft_strdup(envp[i]);
		i++;
	}
	data->pid = -1;
	data->env[i] = NULL;
	data->cmd = NULL;
	data->ret = 0;
	data->err = 0;
	data->i = 0;
	data->arg = 0;
	data->status = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_data				data;

	if (argc != 1)
		return (0);
	(void)argv;
	signals_handler();
	init_data(&data, envp);
	shlevel(&data);
	shell_loop(&data);
}
