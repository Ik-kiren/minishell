/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:37:47 by cdupuis           #+#    #+#             */
/*   Updated: 2023/11/29 12:22:14 by cdupuis          ###   ########.fr       */
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
	char	*end_cwd;

	if (!getcwd(cwd, 4096))
		printf("error cwd\n");
	end_cwd = get_lcwd(cwd);
	prompt = get_prompt(data, end_cwd);
	line = NULL;
	line = readline(prompt);
	free(prompt);
	if (!line)
		return (NULL);
	add_history(line);
	return (line);
}
