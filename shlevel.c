/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlevel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: n43 <n43@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:56:17 by n43               #+#    #+#             */
/*   Updated: 2024/01/18 16:57:17 by n43              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_shlvl(t_data *data, int lvl)
{
	char	*str;

	unset_env_variable(data, "SHLVL");
	if (lvl > 999)
	{
		lvl = 1;
		printf("minishell: warning: reset SHLVL to 1\n");
	}
	if (lvl < 0)
		lvl = 0;
	str = ft_itoa(lvl);
	str = ft_strjoin_f1("SHLVL=", str);
	set_env_variable(data, str);
	free_ptr(str);
}

void	shlevel(t_data *data)
{
	int		i;
	int		lvl;

	i = get_env_idx(data, "SHLVL");
	if (i == -1)
		set_env_variable(data, "SHLVL=1");
	else
	{
		i = get_env_idx(data, "SHLVL");
		lvl = ft_atoi(data->env[i] + 6);
		lvl++;
		set_shlvl(data, lvl);
	}
}
