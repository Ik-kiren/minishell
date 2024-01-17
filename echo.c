/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daribeir <daribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:02:31 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/17 21:52:32 by daribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_echo(char **tokens, int *k, int *arg)
{
	int	i;
	int	j;

	j = 1;
	while (tokens[j])
	{
		i = 0;
		while (tokens[j][i])
		{
			if (tokens[j][0] != '-')
			{
				*k = j - 1;
				return ;
			}
			if (tokens[j][i] != 'n' && i != 0)
			{
				*k = j - 1;
				return ;
			}
			i++;
		}
		*arg += 1;
		j++;
	}
}

int	shell_echo(t_data *data, char **tokens)
{
	data->i = 1;
	data->arg = 0;
	while (tokens[data->i])
	{
		if (tokens[1][0] == '-' && tokens[1][1] == 'n')
		{
			check_echo(tokens, &(data->i), &(data->arg));
			while (tokens[data->i + 1])
			{
				printf("%s", tokens[++(data->i)]);
				if (tokens[data->i + 1])
					printf(" ");
			}
			break ;
		}
		else
			printf("%s", tokens[data->i]);
		(data->i) += 1;
		if (tokens[data->i])
			printf(" ");
	}
	if (data->arg == 0)
		printf("\n");
	data->ret = 0;
	return (1);
}
