/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:43:40 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/08 12:09:43 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_here_exit(int signal, siginfo_t *r_info, void *s)
{
	(void)r_info;
	(void)s;
	(void)signal;
}

void	ignored_here_signal(void)
{
	struct sigaction	ignore;

	ignore.sa_handler = SIG_IGN;
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;
	sigaction(SIGQUIT, &ignore, NULL);
}

void	signals_here_handler(t_data *data)
{
	struct sigaction	response;

	response.sa_sigaction = sig_here_exit;
	sigemptyset(&response.sa_mask);
	response.sa_flags = 0;
	sigaction(SIGINT, &response, NULL);
	ignored_here_signal();
}
