/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:30:18 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/18 12:38:52 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_path(t_data *data)
{
	char	*str;

	str = get_env_var(data, "HOME", NULL);
	data->cmd->args[1] = ft_strjoin_f(get_key_value(str), \
		data->cmd->args[1] + 1);
}
