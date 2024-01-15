/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:30:31 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/15 12:44:03 by cdupuis          ###   ########.fr       */
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

void	fill_in_cmd(t_cmd *tmp, char **tokens, int i, int l)
{
	int	j;

	while (tmp)
	{
		j = i;
		tmp->cmd = ft_strdup(tokens[i]);
		while (tokens[j] && tokens[j][0] != '|'
			&& tokens[j][0] != '>' && tokens[j][0] != '<')
			j++;
		tmp->args = malloc(sizeof(char *) * (j + 1));
		while (tokens[i] && tokens[i][0] != '|'
			&& tokens[i][0] != '>' && tokens[i][0] != '<')
		{
			tmp->args[l++] = ft_strdup(tokens[i++]);
		}
		if (tokens[i] && (tokens[i][0] == '<' || tokens[i][0] == '>'))
			i += 2;
		tmp->pipe = malloc(sizeof(int) * 2);
		pipe(tmp->pipe);
		tmp->args[l] = NULL;
		l = 0;
		tmp = tmp->next;
		i++;
	}
}

void	fill_cmd(char **tokens, t_cmd **cmd)
{
	int		i;
	t_cmd	*tmp;
	int		l;

	tmp = *cmd;
	i = 0;
	l = 0;
	if (!tokens)
		return ;
	fill_in_cmd(tmp, tokens, i, l);
}
