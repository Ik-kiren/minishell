/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:30:18 by cdupuis           #+#    #+#             */
/*   Updated: 2023/11/24 13:24:46 by cdupuis          ###   ########.fr       */
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
		if (cmd->fds)
			close(cmd->fds->fd);
		cmd = cmd->next;
	}
}

int	set_pipes(t_cmd *cmd, t_cmd *c)
{
	if (c->fds != NULL && (c->fds->type == 1 || c->fds->type == 3))
		dup2(c->fds->fd, STDIN_FILENO);
	else if (c->prev)
		dup2(c->prev->pipe[0], STDIN_FILENO);
	if (c->next && c->fds == NULL)
		dup2(c->pipe[1], STDOUT_FILENO);
	else if (c->fds != NULL && c->fds->type == 2)
		dup2(c->fds->fd, STDOUT_FILENO);
	close_pipes(cmd, c);
	if (cmd->fds)
	{
		cmd->fds->stdout_fd = dup(STDOUT_FILENO);
		cmd->fds->stdin_fd = dup(STDIN_FILENO);
		close(c->fds->fd);
		close(cmd->fds->stdout_fd);
		close(cmd->fds->stdin_fd);
	}
	return (1);
}
