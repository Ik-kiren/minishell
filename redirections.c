/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:45:49 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/19 15:08:53 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_last_fd(t_cmd *last)
{
	if (last->fds)
	{
		free_ptr(last->fds->name);
		free_ptr(last->fds);
	}
}

int	parse_redirect3(t_cmd *last, t_data *data, char **tokens, int *i)
{
	if (tokens[*i][0] == '>')
	{
		if (!tokens[*i + 1])
			return (1);
		last = get_last_cmd(data->cmd);
		free_last_fd(last);
		last->fds = new_fds(tokens[*i + 1]);
		last->fds->type = 2;
		last->fds->fd = open(last->fds->name, \
			O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (last->fds->fd == -1)
			last->err = errno;
		*i += 1;
		return (1);
	}
	return (0);
}

int	parse_redirect2(t_cmd *last, t_data *data, char **tokens, int *i)
{
	if (tokens[*i][0] == '<')
	{
		if (!tokens[*i + 1])
			return (1);
		last = get_last_cmd(data->cmd);
		unlink_doc(last);
		last->fdh = new_fds(tokens[*i + 1]);
		last->fdh->type = 1;
		last->fdh->fd = open(last->fdh->name, O_RDONLY);
		if (last->fdh->fd == -1)
			last->err = errno;
		*i += 1;
		return (1);
	}
	return (parse_redirect3(last, data, tokens, i));
}

int	parse_redirect(t_cmd *last, t_data *data, char **tokens, int *i)
{
	if (!ft_strcmp(tokens[*i], ">>"))
	{
		if (!tokens[*i + 1])
			return (1);
		last = get_last_cmd(data->cmd);
		free_last_fd(last);
		last->fds = new_fds(tokens[*i + 1]);
		last->fds->type = 2;
		last->fds->fd = open(last->fds->name,
				O_RDWR | O_APPEND | O_CREAT, 0777);
		if (last->fds->fd == -1)
			last->err = errno;
		*i += 1;
		return (1);
	}
	return (parse_redirect2(last, data, tokens, i));
}
