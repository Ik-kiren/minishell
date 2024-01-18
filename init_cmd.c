/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:30:31 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/18 10:14:19 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd(t_cmd **cmd)
{
	(*cmd)->cmd = NULL;
	(*cmd)->fds = NULL;
	(*cmd)->fdh = NULL;
	(*cmd)->args = NULL;
	(*cmd)->pipe = NULL;
	(*cmd)->prev = NULL;
	(*cmd)->next = NULL;
	(*cmd)->path = NULL;
	(*cmd)->err = -45;
}

t_fds	*new_fds(char *name)
{
	t_fds	*tmp;

	tmp = malloc(sizeof(t_fds));
	tmp->name = ft_strdup(name);
	tmp->fd = 0;
	tmp->type = 0;
	tmp->stdin_fd = -1;
	tmp->stdout_fd = -1;
	return (tmp);
}

t_cmd	*lst_new_cmd(void)
{
	t_cmd	*tmp;

	tmp = malloc(sizeof(t_cmd));
	if (!tmp)
		return (NULL);
	init_cmd(&tmp);
	return (tmp);
}

void	check_args(t_cmd *tmp, char **tokens, int *i)
{
	int	k;

	k = 1;
	tmp->cmd = ft_strdup(tokens[*i]);
	*i += 1;
	tmp->args = malloc(sizeof(char *) * 2);
	tmp->args[0] = ft_strdup(tmp->cmd);
	tmp->args[1] = NULL;
	while (tokens[*i] && tokens[*i][0] != '|')
	{
		if (c_pr(tokens[*i][0]))
			*i += 2;
		while (tokens[*i] && !c_pr(tokens[*i][0]))
		{
			tmp->args = ft_realloc(tmp->args, ft_strdup(tokens[*i]));
			k++;
			*i += 1;
		}
	}
	if (tokens[*i] && tokens[*i][0] == '|')
	{
		*i += 1;
	}
	tmp->pipe = malloc(sizeof(int) * 2);
	pipe(tmp->pipe);
}

void	fill_ic_utils(t_cmd *tmp, char **tokens, int *i)
{
	tmp->cmd = ft_strdup(tokens[*i]);
	tmp->args = malloc(sizeof(char *) * 1);
	tmp->args[0] = NULL;
	while (tokens[*i] && tokens[*i][0] != '|')
	{
		if (tokens[*i][0] == '|')
			*i += 1;
		while (tokens[*i] && tokens[*i][0] != '|'
		&& tokens[*i][0] != '>' && tokens[*i][0] != '<')
		{
			tmp->args = ft_realloc(tmp->args, ft_strdup(tokens[*i]));
			*i += 1;
		}
		while (tokens[*i] && (tokens[*i][0] == '<' || tokens[*i][0] == '>'))
			*i += 2;
	}
	tmp->pipe = malloc(sizeof(int) * 2);
	pipe(tmp->pipe);
}
