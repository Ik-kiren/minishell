/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:32:14 by cdupuis           #+#    #+#             */
/*   Updated: 2023/11/10 14:19:49 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_launch(t_data *data, t_cmd *cmd)
{
	cmd->path = get_path(data, cmd);
	if (execve(cmd->path, cmd->args, data->env) == -1)
	{
		perror("lsh1");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
	return (1);
}


void	launch_cmd(t_cmd *cmd, t_data *data, char **tokens)
{
	set_pipes(data->cmd, cmd);
	close_pipes(data->cmd, NULL);
	launch_builtins(cmd, data, tokens);
	shell_launch(data, cmd);
	exit(EXIT_SUCCESS);
}

int	shell_execute(char **tokens, t_data *data)
{
	t_cmd	*cmd;
	int		status;
    int     builtins;

	cmd = data->cmd;
	status = 0;
	if (tokens == NULL)
		return (1);
	if (tokens[0] == NULL)
		return (1);
	data->stdin_fd = dup(STDOUT_FILENO);
	//printf("id = %d\n", ft_strcmpargs(tokens[0], builtins_str));
    if (!cmd->next)
        builtins = launch_builtins(cmd, data, tokens);
	while (cmd && builtins == 0)
	{
		data->pid = fork();
		if (data->pid == -1)
			return 0;
		else if (data->pid == 0)
		{
			launch_cmd(cmd, data, tokens);
		}
		cmd = cmd->next;
	}
	close_pipes(data->cmd, NULL);
	waitpid(data->pid, &status, WUNTRACED);
	//dup2(data->stdin_fd, STDOUT_FILENO);
	return (1);
}

void	shell_loop(t_data *data)
{
	char	*line;
	char	**tokens;
	int		status;

	while (1)
	{
		line = shell_line(data);
		tokens = shell_split_tokens(line);
		pipe_count(data, tokens);
		//printf("data->cmd = %s\n", data->cmd->cmd);
		fill_cmd(tokens, &data->cmd);
		status = shell_execute(tokens, data);
		clean_cmd(&data->cmd);
		(void)status;
	}
}
