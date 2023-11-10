/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:30:18 by cdupuis           #+#    #+#             */
/*   Updated: 2023/11/10 13:31:08 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_cmd *cmd, t_cmd *skip_cmd)
{
	while (cmd)
	{
		if (cmd != skip_cmd && cmd->pipe)
		{
			close(cmd->pipe[0]);
			close(cmd->pipe[1]);
		}
		cmd = cmd->next;
	}		
}

int	set_pipes(t_cmd *cmd, t_cmd *c)
{
	if (c->prev)
	{
		dup2(c->prev->pipe[0], STDIN_FILENO);
	}
	if (c->next)
	{
		dup2(c->pipe[1], STDOUT_FILENO);
	}
	close_pipes(cmd, c);
	return (1);
}
