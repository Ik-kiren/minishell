#include "minishell.h"

void init_cmd(t_cmd **cmd)
{
	(*cmd)->cmd = "test";
	(*cmd)->args = NULL;
	(*cmd)->pipe = NULL;
	(*cmd)->prev = NULL;
	(*cmd)->next = NULL;
}

t_cmd *lst_new_cmd()
{
	t_cmd *tmp;

	tmp = malloc(sizeof(t_cmd));
	init_cmd(&tmp);
	return (tmp);
}

void add_cmd_lst(t_cmd **lst, t_cmd *new_cmd)
{
	t_cmd *tmp;

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

void	fill_cmd(char **tokens, t_cmd **cmd)
{
	int		i;
	int		j;
	t_cmd	*tmp;
	int		l;

	tmp = *cmd;
	i = 0;
	j = 1;
	l = 0;
	while (tmp)
	{
		tmp->cmd = ft_strdup(tokens[i++]);
		printf("tmp->cmd = %s\n", tmp->cmd);
		while (tokens[i][0] != '|' && tokens[i])
		{
			printf("tmp->cmd = %s\n", tokens[i]);
			i++;
		}
		printf("tmp->cmd = %s\n", tokens[i]);
		tmp->args = malloc(sizeof(char *) * j + 1);
		while (tokens[i][0] != '|')
		{
			tmp->args[l] = ft_strdup(tokens[i]);
			printf("tmp->cmd = %s\n", tmp->args[l]);
			l++;
			i++;
		}
		tmp->args[l] = NULL;
		l = 0;
		tmp = tmp->next;
	}
}
