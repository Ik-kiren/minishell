/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:32:14 by cdupuis           #+#    #+#             */
/*   Updated: 2023/11/28 11:03:44 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_launch(t_data *data, t_cmd *cmd)
{
	cmd->path = get_path(data, cmd);
	if (execve(cmd->path, cmd->args, data->env) == -1)
	{
		data->ret = "0";
		perror(cmd->cmd);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
	return (1);
}

void	launch_cmd(t_cmd *cmd, t_data *data, char **tokens)
{
	int	ret;

	set_pipes(data->cmd, cmd);
	close_pipes(data->cmd, NULL);
	ret = launch_builtins(cmd, data, tokens);
	if (ret == 0)
		shell_launch(data, cmd);
	exit(EXIT_SUCCESS);
}

int	shell_execute(char **tokens, t_data *data)
{
	t_cmd	*cmd;
	int		status;
	int		builtins;

	if (!tokens)
		return (0);
	cmd = data->cmd;
	builtins = 0;
	status = 0;
	if (tokens == NULL)
		return (1);
	if (tokens[0] == NULL)
		return (1);
	if (!cmd->next && !cmd->fds)
		builtins = launch_builtins(cmd, data, tokens);
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
	close_pipes(data->cmd, NULL);
	waitpid(data->pid, &status, WUNTRACED);
	return (1);
}

void	shell_loop(t_data *data)
{
	char	*line;
	char	**tokens;
	int		status;

	status = 0;
	tokens = NULL;
	while (1)
	{
		line = shell_line(data);
		if (!line)
			shell_exit(data, NULL);
		if (line[0] != '\0')
		{
			tokens = shell_split_tokens(data, line);
			pipe_count(data, tokens);
			fill_cmd(tokens, &data->cmd);
			status = shell_execute(tokens, data);
			if (data->cmd->fds && data->cmd->fds->type == 3)
				unlink(data->cmd->fds->name);
			free_str(tokens);
			clean_cmd(&data->cmd);
		}
		(void)status;
	}
}
