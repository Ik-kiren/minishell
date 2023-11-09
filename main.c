/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:51:03 by cdupuis           #+#    #+#             */
/*   Updated: 2023/11/09 13:45:55 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_lcwd(char *str)
{
	char	*tmp;
	int		m_len;
	int		i;
	int		j;

	m_len = ft_strlen(str);
	i = m_len;
	j = 0;
	while (str[i] != '/' && i != 0)
		i--;
	tmp = malloc(sizeof(char) * (m_len - i + 1));
	if (!tmp)
		return (NULL);
	while (str[i])
	{
		tmp[j] = str[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*get_key_value(char *key)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (key[i] != '=')
	{
		i++;
	}
	tmp = malloc(sizeof(char) * (ft_strlen(key) - i + 1));
	if (!tmp)
		return (NULL);
	i++;
	while (key[i])
	{
		tmp[j] = key[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*get_prompt(t_data *data, char *cwd)
{
	char	*end_cwd;
	char	*user;
	char	*tmp;
	char	*prompt;
	int		idx;
	char	*tmp_end;

	idx = get_env_idx(data, "USER");
	tmp_end = get_lcwd(cwd);
	end_cwd = ft_strjoin(tmp_end, "$ ");
	tmp = get_key_value(data->env[idx]);
	user = ft_strjoin(tmp, ":");
	prompt = ft_strjoin(user, end_cwd);
	free(end_cwd);
	free(user);
	free(tmp);
	free(tmp_end);
	return (prompt);
}

char	*shell_line(t_data *data)
{
	char	*line;
	char	cwd[4096];
	char	*prompt;

	if (!getcwd(cwd, 4096))
		printf("error cwd\n");
	prompt = get_prompt(data, cwd);
	line = NULL;
	line = readline(prompt);
	if (!line)
		return (NULL);
	add_history(line);
	free(prompt);
	return (line);
}

/*char	*get_path(t_data *data, char *cmd)
{
	char *path;
	char *tmp_path;
	char *tmp;
	
	tmp_path = get_env_var(data, "PATH");
	path = get_key_value(tmp_path);
	tmp = ft_strjoin(path, "/");
	return (ft_strjoin(tmp, cmd));
}*/

int	shell_launch(t_data *data, t_cmd *cmd)
{
	char	*path;

	path = ft_strjoin("/bin/", cmd->cmd);
	printf("path = =%s=\n", path);
	if (execve(path, cmd->args, data->env) == -1)
	{
		perror("lsh1");
		exit(EXIT_FAILURE);
	}
	return (1);
}

int	ft_strcmpargs(char *s1, char **s2)
{
	int	i;
	int	j;
	int	found;

	j = 0;
	while (j <= 6)
	{
		i = 0 ;
		found = 1;
		while (s1[i])
		{
			if (s1[i] != s2[j][i])
			{
				found = 0;
				break ;
			}
			i++;
		}
		if (found == 1)
		{
			return (j + 1);
		}
		j++;
	}
	return (0);
}

void	launch_cmd(t_cmd *cmd, t_data *data)
{
	int		id;
	char	*builtins_str[] = {
		"cd",
		"echo",
		"pwd",
		"export",
		"unset",
		"env",
		"exit"
	};

	id = 0;
	if ((id = ft_strcmpargs(cmd->cmd, builtins_str)))
	{
		(launch_builtins(id, cmd->args, data));
		exit(EXIT_FAILURE);
	}
	shell_launch(data, cmd);
	exit(EXIT_FAILURE);
}

int	shell_execute(char **tokens, t_data *data)
{
	t_cmd *cmd;
	int status;

	cmd = data->cmd;
	status = 0;
	if (tokens == NULL)
		return (1);
	if (tokens[0] == NULL)
		return (1);
	//printf("id = %d\n", ft_strcmpargs(tokens[0], builtins_str));
	while (cmd)
	{
		data->pid = fork();
		if (data->pid == -1)
			return 0;
		else if (data->pid == 0)
			launch_cmd(cmd, data);
		cmd = cmd->next;
	}
	waitpid(data->pid, &status, WUNTRACED);
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

void	init_data(t_data *data, char **envp)
{
	int	len;
	int	i;

	i = 0;
	len = ft_ptrlen(envp);
	data->env = malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		data->env[i] = ft_strdup(envp[i]);
		i++;
	}
	data->env[i] = NULL;
	data->cmd = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_data				data;

	(void)argc;
	(void)argv;
	signals_handler();
	init_data(&data, envp);
	shell_loop(&data);
}
