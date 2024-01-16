/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:51:06 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/16 12:34:20 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_size(char *token)
{
	int	i;

	i = 0;
	while (token[i] != '=')
		i++;
	return (i);
}

int	shell_cd(t_data *data)
{
	if (data->cmd->args[1] != NULL && data->cmd->args[2] != NULL)
		return (1);
	if (data->cmd->args[1] == NULL)
	{
		chdir(getenv("HOME"));
		set_pwd(data);
	}
	else
	{
		if (chdir(data->cmd->args[1]) != 0)
		{
			data->ret = 1;
			perror(data->cmd->args[1]);
		}
		else
			set_pwd(data);
	}
	return (1);
}

int	shell_echo(t_data *data, char **tokens)
{
	int	i;
	int	arg;

	i = 1;
	arg = 0;
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], "-n"))
		{
			if (tokens[i + 1])
				printf("%s", tokens[++i]);
			arg++;
		}
		else if (ft_strcmp(tokens[i], "-n"))
			printf("%s", tokens[i]);
		i++;
		if (tokens[i])
			printf(" ");
	}
	if (arg == 0)
		printf("\n");
	data->ret = 0;
	return (1);
}

int	shell_exit(t_data *data, char **tok)
{
	int	exit_c;
	int	fail;

	fail = 0;
	exit_c = 0;
	if (tok)
	{
		if (tok[1])
		{
			exit_c = ft_atol((&tok[1]), &fail);
			printf("exit\n");
			if (tok[1] && fail)
			{
				exit_c = 2;
				printf("%s: %s: numeric argument required\n", tok[0], tok[1]);
			}
			else if (ft_ptrlen(tok) > 2)
			{
				printf("%s: too many arguments\n", tok[0]);
				return (1);
			}
			free_str(tok);
		}
	}
	close_pipes(data->cmd, NULL);
	return (free_str(data->env), exit(exit_c), 0);
}

int	launch_builtins(t_cmd *cmd, t_data *data, char **tokens)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(cmd->cmd, "cd"))
		ret = shell_cd(data);
	else if (!ft_strcmp(cmd->cmd, "echo"))
		ret = shell_echo(data, cmd->args);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		ret = shell_pwd(data);
	else if (!ft_strcmp(cmd->cmd, "export"))
		ret = shell_export(tokens, data);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		ret = shell_unset(tokens, data);
	else if (!ft_strcmp(cmd->cmd, "env"))
		ret = shell_env(data);
	else if (!ft_strcmp(cmd->cmd, "exit"))
		ret = shell_exit(data, tokens);
	return (ret);
}
