/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 03:44:50 by daribeir          #+#    #+#             */
/*   Updated: 2024/01/14 16:38:49 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp2(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = -1;
	while (++i, s1[i] && (s1[i] == s2[i]) && (n > 1))
		n--;
	if (n == 0)
		return (0);
	return ((const unsigned char)s1[i] - (const unsigned char)s2[i]);
}
