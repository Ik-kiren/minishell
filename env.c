/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:28:19 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/19 14:03:16 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*len_malloc(char const *s, size_t len)
{
	char	*tab;
	size_t	length;

	length = len + 1;
	if (len > ft_strlen(s))
		length = ft_strlen(s) + 1;
	tab = (char *)malloc(sizeof(char) * length);
	if (!tab)
	{
		free(tab);
		return (NULL);
	}				
	return (tab);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*tab;

	i = start;
	j = 0;
	tab = len_malloc(s, len);
	if (tab == NULL)
		return (NULL);
	if (start > ft_strlen(s))
	{
		tab[j] = '\0';
		return (tab);
	}
	while (s[i])
	{
		if (i >= start && j < len)
		{
			tab[j] = s[i];
			j++;
		}
		i++;
	}
	tab[j] = '\0';
	return (tab);
}

void	set_pwd(t_data *data)
{
	int		idx;
	char	cwd[4096];

	idx = get_env_idx(data, "PWD");
	if (idx == -1)
	{
		set_env_variable(data, getcwd(cwd, 4096));
		return ;
	}
	free(data->env[idx]);
	getcwd(cwd, 4096);
	data->env[idx] = ft_strjoin("PWD=", cwd);
}

int	get_env_idx(t_data *data, char *token)
{
	int		i;
	size_t	len;

	i = 0;
	while (data->env[i])
	{
		len = 0;
		while (data->env[i][len] != '=' && data->env[i][len] != '\0')
			len++;
		if (len <= ft_strlen(token) && (token[len] == '\0'
				|| check_spchar(token[len])))
			len--;
		if (ft_strncmp(data->env[i], token, len))
			return (i);
		i++;
	}
	return (-1);
}

char	*get_env_var(t_data *data, char *token, int *dolars)
{
	char	*tmp;
	int		idx;
	char	*mem;

	if (token[0] == '?')
	{
		*dolars = 1;
		if (ft_strlen(token) > 1)
		{
			tmp = ft_strjoin(ft_itoa(data->ret), token + 1);
			mem = tmp;
			while (tmp && !check_spchar(*tmp))
				tmp++;
		}
		else
			tmp = NULL;
		if (tmp)
			return (ft_substr(mem, 0, tmp - mem));
		else
			return (ft_itoa(data->ret));
	}
	idx = get_env_idx(data, token);
	if (idx == -1)
		return (NULL);
	return (ft_strdup(data->env[idx]));
}
