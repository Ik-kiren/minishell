/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:54:13 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/19 12:42:28 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_direcory(t_cmd *cmd)
{
	struct stat	dir;

	stat(cmd->path, &dir);
	if (S_ISDIR(dir.st_mode) != 0)
	{
		printf("minishell: %s: is a dir\n", cmd->cmd);
		exit(126);
	}
}

void	check_file(t_cmd *cmd)
{
	cmd->path = ft_strdup(cmd->cmd);
	check_direcory(cmd);
	if (access(cmd->cmd, F_OK) == -1)
	{
		perror("minishell");
		exit(127);
	}
	if (cmd->cmd[0] == '.' && access(cmd->cmd, X_OK) == -1)
	{
		perror("minishell");
		exit(126);
	}
	if ((access(cmd->cmd, R_OK || W_OK) == -1))
	{
		perror("minishell");
		exit(1);
	}
}

int	check_cmd(t_data *data, t_cmd *cmd)
{
	if ((cmd->cmd[0] == '.' && cmd->cmd[1] == '/') \
		|| (cmd->cmd[0] == '.' && cmd->cmd[1] == '.' && cmd->cmd[2] == '/') \
		|| cmd->cmd[0] == '/')
	{
		check_file(cmd);
	}
	else
	{
		cmd->path = get_path(data, cmd);
	}
	if (access(cmd->path, F_OK) == -1)
	{
		printf("minishell: %s: command not found\n", cmd->cmd);
		exit(127);
	}
	if (cmd->cmd[0] == '\0')
	{
		printf("minishell: '': command not found\n");
		exit(127);
	}
	return (0);
}
