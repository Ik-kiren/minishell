/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:51:06 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/18 13:28:06 by cdupuis          ###   ########.fr       */
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
		if (data->cmd->args[1][0] == '~')
		{
			cd_path(data);
		}
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

static void	exit_clean(t_data *data, int exit_c)
{
	close_pipes(data->cmd, NULL);
	clean_cmd(&data->cmd);
	free_str(data->env);
	exit(exit_c);
}

int	shell_exit(t_data *data, char **tok)
{
	int	exit_c;
	int	fail;

	fail = 0;
	exit_c = 0;
	printf("exit\n");
	if (tok)
	{
		if (tok[1])
		{
			exit_c = ft_atol((&tok[1]), &fail);
			if (tok[1] && fail)
			{
				exit_c = 2;
				printf("%s: %s: numeric argument required\n", tok[0], tok[1]);
			}
			else if (ft_ptrlen(tok) > 2)
			{
				printf("%s: too many arguments\n", tok[0]);
				return (data->ret = 1, 1);
			}
		}
		free_str(tok);
	}
	return (exit_clean(data, exit_c), 0);
}

int	launch_builtins(t_cmd *cmd, t_data *data, char **tokens)
{
	int	ret;

	ret = 0;
	if (!cmd->cmd)
		return (0);
	if (!ft_strncmp2(cmd->cmd, "cd", ft_strlen(max(cmd->cmd, "cd"))))
		ret = shell_cd(data);
	else if (!ft_strncmp2(cmd->cmd, "echo", ft_strlen(max(cmd->cmd, "echo"))))
		ret = shell_echo(data, cmd->args);
	else if (!ft_strncmp2(cmd->cmd, "pwd", ft_strlen(max(cmd->cmd, "pwd"))))
		ret = shell_pwd(data);
	else if (!ft_strncmp2(cmd->cmd, "export" \
	, ft_strlen(max(cmd->cmd, "export"))))
		ret = shell_export(tokens, data);
	else if (!ft_strncmp2(cmd->cmd, "unset", ft_strlen(max(cmd->cmd, "unset"))))
		ret = shell_unset(tokens, data);
	else if (!ft_strncmp2(cmd->cmd, "env", ft_strlen(max(cmd->cmd, "env"))))
		ret = shell_env(data);
	else if (!ft_strncmp2(cmd->cmd, "exit", ft_strlen(max(cmd->cmd, "exit"))))
		ret = shell_exit(data, tokens);
	return (ret);
	close_pipes(data->cmd, NULL);
}
