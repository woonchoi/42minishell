/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasong <jasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 23:45:42 by woonchoi          #+#    #+#             */
/*   Updated: 2022/05/30 18:24:30 by jasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_status;

static void	sigint_handler(pid_t pid)
{
	if (pid == -1)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		ft_putendl_fd("", STDOUT_FILENO);
	g_exit_status = 130;
}

static void	sigquit_handler(void)
{
	ft_putstr_fd("Quit: 3", STDERR_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	signal_handler(int signum)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signum == SIGINT)
		sigint_handler(pid);
	else if (signum == SIGQUIT)
		sigquit_handler();
}

void	set_signal()
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
