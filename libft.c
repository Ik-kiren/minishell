/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:11:16 by cdupuis           #+#    #+#             */
/*   Updated: 2023/11/21 14:06:02 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	write (fd, s, len);
}

void	ft_putendl_fd(char *s, int fd)
{
	char	*tmp;

	tmp = ft_strjoin(s, "\n");
	ft_putstr_fd(tmp, fd);
	free(tmp);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strncmp(char *s1, char *s2, int size)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && i <= size)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

size_t	ft_ptrlen(char **str)
{
	size_t	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
