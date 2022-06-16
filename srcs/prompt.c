/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 23:50:54 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/16 19:06:04 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*preadline(char *shellname)
{
	char	*cmdline;

	signal(SIGQUIT, SIG_IGN);
	cmdline = readline(shellname);
	set_signal();
	return (cmdline);
}

void	prompt(t_info *info)
{
	while (TRUE)
	{
		init_prompt_cycle(info);
		info->input = preadline("minishell$ ");
		if (!info->input)
		{
			rl_replace_line("", 0);
			printf("exit\n");
			exit(0);
		}
		add_history(info->input);
		lexer(info);
		scanner(info);
		parser(info);
		executor(info);
		terminate_free(info);
	}
}
