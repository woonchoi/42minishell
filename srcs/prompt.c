/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 23:50:54 by woonchoi          #+#    #+#             */
/*   Updated: 2022/05/21 00:00:49 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//prototype of prompt
#include "../includes/minishell.h"

char	*preadline(char *shellname)
{
	char	*cmdline;

	signal(SIGQUIT, SIG_IGN);
	cmdline = readline(shellname);
	set_signal();
	return (cmdline);
}

void	prompt()
{
	char	*input;

	while(1)
	{
		input = preadline("minishell$ ");
		if (!input)
		{
			rl_replace_line("", 0);
			printf("exit\n");
			exit(0);
		}
		add_history(input);
		free(input);
	}
}
