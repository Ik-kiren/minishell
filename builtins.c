/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:51:06 by cdupuis           #+#    #+#             */
/*   Updated: 2023/11/06 13:49:12 by cdupuis          ###   ########.fr       */
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

int	shell_cd(char **tokens, t_data *data)
{
	int		idx;
	char	cwd[4096];

	idx = get_env_idx(data, "PWD");
	if (tokens[1] == NULL)
		fprintf(stderr, "pathname error");
	else
	{
		if (chdir(tokens[1]) != 0)
			perror("lsh");
		else
		{
			printf("idx = %d\n", idx);
			free(data->env[idx]);
			getcwd(cwd, 4096);
			data->env[idx] = ft_strjoin("PWD=", cwd);
		}
	}
	return (1);
}

int	shell_echo(char **tokens)
{
	int	i;
	int	arg;

	i = 1;
	arg = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "-n"))
		{
			printf("%s", tokens[++i]);
			arg++;
		}
		else
			printf("%s", tokens[i]);
		i++;
	}
	if (arg == 0)
		printf("\n");
	return (1);
}

int	shell_exit(t_data *data, char **tokens)
{
	if (tokens[1] != NULL)
		return (0);
	free_ptr(data->env);
	free_ptr(tokens);
	printf("exit\n");
	exit(EXIT_SUCCESS);
	return (1);
}

int	launch_builtins(int id, char **tokens, t_data *data)
{
	int	ret;

	ret = 0;
	if (id == 1)
		ret = shell_cd(tokens, data);
	else if (id == 2)
		ret = shell_echo(tokens);
	else if (id == 3)
		ret = shell_pwd(tokens, data);
	else if (id == 4)
		ret = shell_export(tokens, data);
	else if (id == 5)
		ret = shell_unset(tokens, data);
	else if (id == 6)
		ret = shell_env(data, tokens);
	else if (id == 7)
		ret = shell_exit(data, tokens);
	return (ret);
}
