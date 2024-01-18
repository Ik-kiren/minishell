/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:49:14 by cdupuis           #+#    #+#             */
/*   Updated: 2024/01/18 14:17:18 by cdupuis          ###   ########.fr       */
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
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;
	sigaction(SIGQUIT, &ignore, NULL);
}

void	signal_print_newline(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
}

void	set_signals_noninteractive(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_handler = &signal_print_newline;
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

void	signals_handler(t_data *data)
{
	struct sigaction	response;

	response.sa_sigaction = sig_exit;
	sigemptyset(&response.sa_mask);
	response.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &response, NULL);
	data->ret = errno;
	ignored_signal();
}
