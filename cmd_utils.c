/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:30:46 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/06 14:46:25 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*get_last_cmd(t_cmd *cmd)
{
	while (cmd->next)
	{
		cmd = cmd->next;
	}
	return (cmd);
}

void	free_cmd(t_cmd *cmd)
{
	free_str(cmd->args);
	free_ptr(cmd->cmd);
	free_ptr(cmd->pipe);
	free_ptr(cmd->path);
	free_ptr(cmd);
}

void	clean_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = NULL;
	if (!cmd)
		return ;
	while (*cmd)
	{
		tmp = (*cmd)->next;
		if ((*cmd)->fds)
		{
			free_ptr((*cmd)->fds->name);
			free_ptr((*cmd)->fds);
		}
		free_cmd(*cmd);
		*cmd = tmp;
	}
}

void	add_cmd_lst(t_cmd **lst, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	tmp = *lst;
	if (tmp == NULL)
	{
		*lst = new_cmd;
		return ;
	}
	if (new_cmd)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
		new_cmd->prev = tmp;
	}
}
