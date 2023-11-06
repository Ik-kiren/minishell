/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:49:14 by cdupuis           #+#    #+#             */
/*   Updated: 2023/11/06 12:43:52 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_exit(int signal, siginfo_t *r_info, void *s)
{
	(void)r_info;
	(void)s;
	(void)signal;
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ignored_signal(void)
{
	struct sigaction	ignore;

	ignore.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &ignore, NULL);
}

void	signals_handler(void)
{
	struct sigaction	response;

	response.sa_sigaction = sig_exit;
	sigemptyset(&response.sa_mask);
	response.sa_flags = 0;
	sigaction(SIGINT, &response, NULL);
	ignored_signal();
}
