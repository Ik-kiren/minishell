/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 04:57:47 by daribeir          #+#    #+#             */
/*   Updated: 2024/01/22 15:48:16 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*max(char *s1, char *s2)
{
	if (ft_strlen(s1) > ft_strlen(s2))
		return (s1);
	else
		return (s2);
}

static int	go_to_number(char **str, int i, int *signe)
{
	while (((*str)[i] >= 9 && (*str)[i] <= 13) || (*str)[i] == ' ')
		i++;
	if ((*str)[i] == '-')
		*signe = -(*signe);
	if ((*str)[i] == '+' || (*str)[i] == '-')
		i++;
	return (i);
}

static long long	get_atol_return(char *str, int i)
{
	long long	result;

	result = 0;
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result);
}

int	ft_atol(char **str, int *fail)
{
	int		signe;

	signe = 1;
	if (!(ft_isnumber((*str) + go_to_number(str, 0, &signe))))
		return (*fail = 1, 2);
	if ((*str)[0] != '-')
	{
		if (ft_strlen(*str) < 19)
			return (*fail = 0, \
				get_atol_return(*str, go_to_number(str, 0, &signe)) * signe);
		else if (ft_strlen(*str) > 19)
			return (*fail = 1, 2);
		else if (ft_strncmp2("9223372036854775807", *str, \
		ft_strlen(max("9223372036854775807", *str))) < 0)
			return (*fail = 1, 2);
	}
	else if (ft_strlen(*str) < 20)
		return (*fail = 0, \
			get_atol_return(*str, go_to_number(str, 0, &signe)) * signe);
	else if (ft_strlen(*str) > 20)
		return (*fail = 1, 2);
	else if (ft_strncmp2("-9223372036854775808", *str, \
		ft_strlen(max("-9223372036854775808", *str))) < 0)
		return (*fail = 1, 2);
	return (get_atol_return(*str, go_to_number(str, 0, &signe)) * signe);
}
