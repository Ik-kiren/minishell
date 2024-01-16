/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:22:16 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/16 14:39:45 by cdupuis          ###   ########.fr       */
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

int check_cmd(t_data *data, t_cmd *cmd)
{
	//char	cwd[4096];

	if ((cmd->cmd[0] == '.' && cmd->cmd[1] == '/') \
		|| (cmd->cmd[0] == '.' && cmd->cmd[1] == '.' && cmd->cmd[2] == '/') \
		|| cmd->cmd[0] == '/')
	{
		cmd->path = ft_strdup(cmd->cmd);
		if(access(cmd->cmd, F_OK) == -1)
			exit(127);
		if(access(cmd->cmd, X_OK) == -1)
			exit(126);
	}
	else
		cmd->path = get_path(data, cmd);
	return (0);
}

int	execute_child(t_cmd *cmd, t_data *data, char **tokens, int builtins)
{
	int	status;

	status = 0;
	/*if (cmd->cmd[0] == '.')
	{
		cmd->args[0] = ft_strdup(ft_strjoin(getcwd(cwd, 4096), cmd->cmd + 1));
	}*/
	while (cmd && builtins == 0 && cmd->cmd[0] != '<')
	{
		data->pid = fork();
		if (data->pid == -1)
			return (0);
		else if (data->pid == 0)
		{
			if (cmd->err != -45)
			{
				perror("minishell");
				exit(cmd->err);
			}
			check_cmd(data, cmd);
			launch_cmd(cmd, data, tokens);
		}
		cmd = cmd->next;
	}
	if (builtins == 0)
	{
		status = get_children(data);
		data->ret = status % 256;
	}
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
