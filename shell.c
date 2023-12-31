/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:32:14 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/11 10:53:23 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_launch(t_data *data, t_cmd *cmd)
{
	cmd->path = get_path(data, cmd);
	if (execve(cmd->path, cmd->args, data->env) == -1)
	{
		data->ret = 1;
		perror(cmd->cmd);
		shell_exit(data, NULL);
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

void	shell_loop2(char **tokens, t_data *data)
{
	fill_cmd(tokens, &data->cmd);
	shell_execute(tokens, data);
	if (data->cmd->fds && data->cmd->fds->type == 3)
		unlink(data->cmd->fds->name);
}

void	shell_loop(t_data *data)
{
	char	*line;
	char	**tokens;

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
			if (data->err == 0 && tokens)
				shell_loop2(tokens, data);
			free_str(tokens);
			clean_cmd(&data->cmd);
			data->err = 0;
		}
		else
			free_ptr(line);
	}
}
