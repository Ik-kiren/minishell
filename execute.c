/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:22:16 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/06 18:12:54 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_children(t_data *data)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	close_pipes(data->cmd, NULL);
	save_status = 0;
	wpid = 0;
	status = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == data->pid)
			save_status = status;
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

int	execute_child(t_cmd *cmd, t_data *data, char **tokens, int builtins)
{
	int	status;

	status = 0;
	while (cmd && builtins == 0)
	{
		data->pid = fork();
		if (data->pid == -1)
			return (0);
		else if (data->pid == 0)
		{
			launch_cmd(cmd, data, tokens);
		}
		cmd = cmd->next;
	}
	status = get_children(data);
	if (status == 0)
		data->ret = set_ret('0', data->ret);
	else
		data->ret = set_ret('1', data->ret);
	return (1);
}

int	shell_execute(char **tokens, t_data *data)
{
	t_cmd	*cmd;
	int		builtins;

	if (!tokens)
		return (0);
	cmd = data->cmd;
	builtins = 0;
	if (tokens[0] == NULL)
		return (1);
	if (cmd && !cmd->next && !cmd->fds)
		builtins = launch_builtins(cmd, data, tokens);
	if (execute_child(cmd, data, tokens, builtins) == 0)
		return (0);
	return (1);
}
