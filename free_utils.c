/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: n43 <n43@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:23:36 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/18 16:33:01 by n43              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_free(void *ptr1, void *ptr2)
{
	free_ptr(ptr1);
	free_ptr(ptr2);
}

void	free_str(char **str)
{
	int	i;

	i = 0;
	if (str != NULL)
	{
		while (str[i])
		{
			free_ptr(str[i]);
			str[i] = NULL;
			i++;
		}
		free_ptr(str);
		str = NULL;
	}
}

void	*free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}
