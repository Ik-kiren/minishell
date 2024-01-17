/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daribeir <daribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:30:18 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/17 21:40:02 by daribeir         ###   ########.fr       */
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
		if (cmd->fdh)
			close(cmd->fdh->fd);
		cmd = cmd->next;
	}
}

static void	close_them(t_cmd *cmd)
{
	close(cmd->fds->stdout_fd);
	close(cmd->fds->stdin_fd);
}

int	set_pipes(t_cmd *cmd, t_cmd *c)
{
	if (c->fdh)
	{
		dup2(c->fdh->fd, STDIN_FILENO);
		if (c->fds)
			dup2(c->fds->fd, STDOUT_FILENO);
	}
	else if (c->fds != NULL && (c->fds->type == 1 || c->fds->type == 3))
		dup2(c->fds->fd, STDIN_FILENO);
	else if (c->prev)
		dup2(c->prev->pipe[0], STDIN_FILENO);
	if (c->next && c->fds == NULL)
		dup2(c->pipe[1], STDOUT_FILENO);
	else if (c->fds != NULL && c->fds->type == 2)
		dup2(c->fds->fd, STDOUT_FILENO);
	if (c->fds && c->next && !c->next->fds
		&& (c->fds->type == 1 || c->fds->type == 3))
		dup2(c->pipe[1], STDOUT_FILENO);
	close_pipes(cmd, c);
	if (cmd->fds)
	{
		cmd->fds->stdout_fd = dup(STDOUT_FILENO);
		cmd->fds->stdin_fd = dup(STDIN_FILENO);
		close_them(cmd);
	}
	return (1);
}

int	pipe_count(t_data *data, char **tokens)
{
	int		i;
	int		count;
	t_cmd	*last;

	i = -1;
	count = 0;
	last = NULL;
	if (!tokens)
		return (0);
	add_cmd_lst(&data->cmd, lst_new_cmd());
	while (tokens[++i])
	{
		if (tokens[i][0] == '|' )
		{
			add_cmd_lst(&data->cmd, lst_new_cmd());
			count++;
		}
		else if (!ft_strcmp(tokens[i], "<<"))
			count += heredoc_redirect(last, data, tokens, i);
		else
		{
			count += parse_redirect(last, data, tokens, &i);
		}
	}
	return (count);
}
