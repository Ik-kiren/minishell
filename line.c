/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:37:47 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/14 10:30:52 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt(t_data *data, char *tmp_end)
{
	char	*end_cwd;
	char	*user;
	char	*tmp;
	char	*prompt;
	int		idx;

	idx = get_env_idx(data, "USER");
	if (idx == -1)
		tmp = ft_strdup("bash");
	else
	{
		tmp = ft_strdup(data->env[idx]);
		tmp = get_key_value(tmp);
	}
	end_cwd = ft_strjoin(tmp_end, "$ ");
	user = ft_strjoin(tmp, ":");
	prompt = ft_strjoin(user, end_cwd);
	free_ptr(end_cwd);
	free_ptr(user);
	free_ptr(tmp);
	free_ptr(tmp_end);
	return (prompt);
}

char	*shell_line(t_data *data)
{
	char	*line;
	char	cwd[4096];
	char	*prompt;
	char	*end_cwd;

	if (!getcwd(cwd, 4096))
		printf("error cwd\n");
	end_cwd = get_lcwd(cwd);
	prompt = get_prompt(data, end_cwd);
	line = NULL;
	signals_handler();
	line = readline(prompt);
	set_signals_noninteractive();
	free(prompt);
	if (!line)
		return (NULL);
	add_history(line);
	return (line);
}
