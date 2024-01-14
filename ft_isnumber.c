/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 01:12:15 by daribeir          #+#    #+#             */
/*   Updated: 2024/01/14 16:44:38 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isnum(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isnumber(char *str)
{
	int	i;
	int	ret;

	ret = 1;
	i = -1;
	while (++i, str[i])
		if (!(ft_isnum(str[i])))
			ret = 0;
	return (ret);
}
