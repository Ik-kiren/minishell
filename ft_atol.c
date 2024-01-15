/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daribeir <daribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 04:57:47 by daribeir          #+#    #+#             */
/*   Updated: 2024/01/15 05:08:23 by daribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*max(char *s1, char *s2)
{
	if (ft_strlen(s1) > ft_strlen(s2))
		return (s1);
	else
		return (s2);
}

static int	go_to_number(char **str, int i, size_t *signe)
{
	while (((*str)[i] >= 9 && (*str)[i] <= 13) || (*str)[i] == ' ')
		i++;
	if ((*str)[i] == '-')
		*signe = -(*signe);
	if ((*str)[i] == '+' || (*str)[i] == '-')
		i++;
	return (i);
}

int	ft_atol(char **str, int *fail)
{
	size_t		i;
	long long	result;
	size_t		signe;

	i = 0;
	result = 0;
	signe = 1;
	i = go_to_number(str, i, &signe);
	if (!(ft_isnumber((*str) + i)))
		return (*fail = 1, 2);
	if ((*str)[0] != '-')
	{
		if (ft_strncmp2("9223372036854775807", *str, \
			ft_strlen(max("9223372036854775807", *str))) < 0)
			return (*fail = 1, 2);
	}
	else if (ft_strncmp2("-9223372036854775808", *str, \
		ft_strlen(max("-9223372036854775808", *str))) < 0)
		return (*fail = 1, 2);
	while (ft_isdigit((*str)[i]))
	{
		result = result * 10 + (*str)[i] - '0';
		i++;
	}
	return (result * signe);
}
