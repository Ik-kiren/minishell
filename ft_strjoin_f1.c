/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_f1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: n43 <n43@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:04:48 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/18 16:55:30 by n43              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_f1(char const *s1, char *s2)
{
	char	*s;
	size_t	len;
	int		i;

	len = ft_strlen(s1) + ft_strlen(s2);
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	len = 0;
	while (s1[len])
	{
		s[len] = s1[len];
		len++;
	}
	i = 0;
	while (s2[i])
	{
		s[len + i] = s2[i];
		i++;
	}
	s[len + i] = '\0';
	free_ptr(s2);
	return (s);
}
