/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daribeir <daribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:30:31 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/17 21:57:44 by daribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_in_cmd(t_cmd *tmp, char **tokens, int i)
{
	while (tmp)
	{
		while ((tokens[i][0] == '<' || tokens[i][0] == '>') && tokens[i + 2] && \
		(c_pr(tokens[i + 2][0]) || !tokens[i + 3]))
			i += 2;
		if ((tokens[i][0] == '<' || tokens[i][0] == '>') && tokens[i + 2] && \
		(!c_pr(tokens[i + 2][0]) || !tokens[i + 3]))
		{
			i += 2;
			check_args(tmp, tokens, &i);
		}
		else if (!(tokens[i][0] == '<' || tokens[i][0] == '>'))
		{
			fill_ic_utils(tmp, tokens, &i);
			i++;
		}
		tmp = tmp->next;
	}
}

void	fill_cmd(char **tokens, t_cmd **cmd)
{
	int		i;
	t_cmd	*tmp;

	tmp = *cmd;
	i = 0;
	if (!tokens)
		return ;
	fill_in_cmd(tmp, tokens, i);
}
