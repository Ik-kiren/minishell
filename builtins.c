/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:51:06 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/06 12:56:52 by cdupuis          ###   ########.fr       */
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
			data->ret = set_ret('1', data->ret);
			perror("bash");
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
			printf("%s", tokens[++i]);
			arg++;
		}
		else
			printf("%s", tokens[i]);
		i++;
		if (tokens[i])
			printf(" ");
	}
	if (arg == 0)
		printf("\n");
	data->ret = set_ret('1', data->ret);
	return (1);
}

int	shell_exit(t_data *data, char **tokens)
{
	int	exit_c;

	exit_c = 0;
	if (tokens)
	{
		if (ft_ptrlen(tokens) > 2)
		{
			printf("%s: too many arguments\n", tokens[0]);
			return (1);
		}
		if (tokens[1] && !check_number(tokens[1]))
		{
			printf("%s: %s: numeric argument required\n", tokens[0], tokens[1]);
			return (1);
		}
		if (tokens[1])
			exit_c = ft_atoi(tokens[1]);
		free_str(tokens);
	}
	free_ptr(data->ret);
	free_str(data->env);
	exit(exit_c);
	return (1);
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
