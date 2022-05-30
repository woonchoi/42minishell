/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 23:50:54 by woonchoi          #+#    #+#             */
/*   Updated: 2022/05/26 15:24:34 by woonchoi         ###   ########.fr       */
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

void	prompt(t_mshell_info *info)
{
	while(1)
	{
		info->input = preadline("minishell$ ");
		if (!info->input)
		{
			rl_replace_line("", 0);
			printf("exit\n");
			exit(0);
		}
		add_history(info->input);
		free(info->input);
	}
}
