/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:22:16 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/18 21:20:38 by cdupuis          ###   ########.fr       */
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

int	check_cmd(t_data *data, t_cmd *cmd)
{
	if ((cmd->cmd[0] == '.' && cmd->cmd[1] == '/') \
		|| (cmd->cmd[0] == '.' && cmd->cmd[1] == '.' && cmd->cmd[2] == '/') \
		|| cmd->cmd[0] == '/')
	{
		cmd->path = ft_strdup(cmd->cmd);
		if ((access(cmd->cmd, R_OK || W_OK) == -1))
		{
			perror("minishell");
			exit(1);
		}
		else if (access(cmd->cmd, F_OK) == -1)
		{
			perror("minishell");
			exit(127);
		}
		else if (access(cmd->cmd, X_OK) == -1)
		{
			perror("minishell");
			exit(126);
		}
	}
	else
	{
		cmd->path = get_path(data, cmd);
	}
	return (0);
}

void	free_exe(t_data *data, t_cmd *cmd, char **tokens)
{
	int	err;

	err = cmd->err;
	free_str(data->env);
	clean_cmd(&cmd);
	free_str(tokens);
	perror("minishell");
	exit(err);
}

int	execute_child(t_cmd *cmd, t_data *data, char **tokens, int builtins)
{
	data->status = 0;
	if (!cmd->cmd)
		printf("minishell: i need a good command line moron\n");
	while (cmd && cmd->cmd && builtins == 0 && cmd->cmd[0] != '<')
	{
		data->pid = fork();
		if (data->pid == -1)
			return (0);
		else if (data->pid == 0)
		{
			if (cmd->err != -45)
				free_exe(data, cmd, tokens);
			check_cmd(data, cmd);
			launch_cmd(cmd, data, tokens);
		}
		cmd = cmd->next;
	}
	if (builtins == 0)
	{
		data->status = get_children(data);
		data->ret = data->status % 256;
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
