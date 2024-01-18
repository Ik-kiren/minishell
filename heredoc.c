/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:26:41 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/18 11:44:48 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_heredoc(t_data *data, char *delimiter, int fd)
{
	char	*line;

	data->doc = 1;
	while (data->doc)
	{
		signals_handler(data);
		line = readline(">");
		set_signals_noninteractive();
		if (!line || !ft_strcmp(line, delimiter))
		{
			free_ptr(line);
			break ;
		}
		if (ft_strchr('$', line))
			line = replace_env_var(data, line);
		ft_putendl_fd(line, fd);
		free_ptr(line);
	}
}

int	heredoc_redirect(t_cmd *last, t_data *data, char **tokens, int i)
{
	int		tmp_fd;
	char	*name;

	if (!tokens[i + 1])
	{
		data->err = 1;
		return (1);
	}
	last = get_last_cmd(data->cmd);
	unlink_doc(last);
	name = ft_strjoin_f2(ft_strjoin("/dev/shm/", tokens[i + 1]), ft_itoa(i));
	last->fdh = new_fds(name);
	last->fdh->type = 3;
	tmp_fd = open(last->fdh->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	fill_heredoc(data, tokens[i + 1], tmp_fd);
	close(tmp_fd);
	last->fdh->fd = open(last->fdh->name, O_RDONLY);
	free(name);
	return (1);
}
