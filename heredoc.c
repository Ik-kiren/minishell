/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:26:41 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/14 11:28:50 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_heredoc(t_data *data, char *delimiter, int fd)
{
	char	*line;

	data->doc = 1;
	while (data->doc)
	{
		signals_handler();
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
	int	tmp_fd;

	if (!tokens[i + 1])
	{
		data->err = 1;
		return (1);
	}
	last = get_last_cmd(data->cmd);
	last->fds = new_fds(tokens[i + 1]);
	last->fds->type = 3;
	tmp_fd = open(last->fds->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	fill_heredoc(data, tokens[i + 1], tmp_fd);
	close(tmp_fd);
	last->fds->fd = open(last->fds->name, O_RDONLY);
	return (1);
}
