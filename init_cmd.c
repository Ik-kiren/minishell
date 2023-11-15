/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:30:31 by cdupuis           #+#    #+#             */
/*   Updated: 2023/11/15 12:46:32 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_cmd(t_cmd **cmd)
{
	(*cmd)->cmd = NULL;
	(*cmd)->args = NULL;
	(*cmd)->pipe = NULL;
	(*cmd)->prev = NULL;
	(*cmd)->next = NULL;
	(*cmd)->path = NULL;
}

t_cmd *lst_new_cmd()
{
	t_cmd *tmp;

	tmp = malloc(sizeof(t_cmd));
	if (!tmp)
		return NULL;
	init_cmd(&tmp);
	return (tmp);
}

void	add_cmd_lst(t_cmd **lst, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	tmp = *lst;
	if (tmp == NULL)
	{
		*lst = new_cmd;
		return ;
	}
	if (lst, *lst, new_cmd)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
		new_cmd->prev = tmp;
	}
}

int	pipe_count(t_data *data, char **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!tokens)
		return 0;
	add_cmd_lst(&data->cmd, lst_new_cmd());
	while (tokens[i])
	{
		if (tokens[i][0] == '|')
		{
			add_cmd_lst(&data->cmd, lst_new_cmd());
			count++;
		}
		i++;
	}
	return (count);
}

t_cmd	*get_last_cmd(t_cmd *cmd)
{
	while (cmd->next)
	{
		cmd = cmd->next;
	}
	return(cmd);
}

void	free_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	tmp = NULL;
	i = 0;
	free_str(cmd->args);
	free(cmd->cmd);
	free(cmd->pipe);
	free_ptr(cmd);
}

void	clean_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = NULL;
	if (!cmd)
		return ;
	while (*cmd)
	{
		tmp = (*cmd)->next;
		free_cmd(*cmd);
		*cmd = tmp;
	}
}

void	fill_cmd(char **tokens, t_cmd **cmd)
{
	int		i;
	int		j;
	t_cmd	*tmp;
	int		l;

	tmp = *cmd;
	i = 0;
	j = 0;
	l = 0;
	if (!tokens)
		return ;
	while (tmp)
	{
		j = 0;
		tmp->cmd = ft_strdup(tokens[i]);
		//printf("tmp->cmd = %s\n", tmp->cmd);
		while (tokens[j] && tokens[j][0] != '|')
			j++;
		//printf("cmd j = %d\n", j);
		tmp->args = malloc(sizeof(char *) * (j + 1));
		while (tokens[i] && tokens[i][0] != '|')
		{
			tmp->args[l] = ft_strdup(tokens[i]);
			//printf("tmp->args = %s\n", tmp->args[l]);
			l++;
			i++;
		}
		tmp->pipe = malloc(sizeof(int) * 2);
		pipe(tmp->pipe);
		tmp->args[l] = NULL;
		l = 0;
		tmp = tmp->next;
		i++;
	}
}
