/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:22:16 by cdupuis           #+#    #+#             */
/*   Updated: 2023/11/29 11:30:01 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	close_pipes(data->cmd, NULL);
	waitpid(data->pid, &status, WUNTRACED);
	return (1);
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
	if (tokens[0] == NULL)
		return (1);
	if (!cmd && !cmd->next && !cmd->fds)
		builtins = launch_builtins(cmd, data, tokens);
	if (execute_child(cmd, data, tokens, builtins) == 0)
		return (0);
	return (1);
}
