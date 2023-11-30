/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:51:06 by cdupuis           #+#    #+#             */
/*   Updated: 2023/11/30 14:35:52 by cdupuis          ###   ########.fr       */
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
	int		idx;
	char	cwd[4096];

	idx = get_env_idx(data, "PWD");
	if (data->cmd->args[1] == NULL)
	{
		chdir(getenv("HOME"));
		getcwd(cwd, 4096);
		data->env[idx] = ft_strjoin("PWD=", cwd);
	}
	else
	{
		if (chdir(data->cmd->args[1]) != 0)
		{
			data->ret = set_ret('0', data->ret);
			perror("lsh");
		}
		else
		{
			free(data->env[idx]);
			getcwd(cwd, 4096);
			data->env[idx] = ft_strjoin("PWD=", cwd);
		}
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
	if (tokens)
	{
		if (tokens[1] != NULL)
			return (0);
		free_str(tokens);
	}
	free_ptr(data->ret);
	free_str(data->env);
	exit(EXIT_SUCCESS);
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
		ret = shell_pwd(tokens, data);
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
