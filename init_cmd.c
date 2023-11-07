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
