/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: n43 <n43@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:32:14 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/18 16:49:36 by n43              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_launch(t_data *data, t_cmd *cmd)
{
	if (execve(cmd->path, cmd->args, data->env) == -1)
	{
		perror(cmd->cmd);
		clean_cmd(&cmd);
	}
	exit(EXIT_FAILURE);
}

void	launch_cmd(t_cmd *cmd, t_data *data, char **tokens)
{
	int	ret;

	set_pipes(data->cmd, cmd);
	close_pipes(data->cmd, NULL);
	ret = launch_builtins(cmd, data, tokens);
	free_str(tokens);
	if (ret == 0)
		shell_launch(data, cmd);
	else
	{
		free_str(data->env);
		clean_cmd(&cmd);
	}
	exit(EXIT_SUCCESS);
}

void	shell_loop2(char **tokens, t_data *data)
{
	fill_cmd(tokens, &data->cmd);
	shell_execute(tokens, data);
}

void	shell_loop3(t_data *data)
{
	if (data->cmd)
		clean_cmd(&data->cmd);
	shell_exit(data, NULL);
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
			shell_loop3(data);
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
