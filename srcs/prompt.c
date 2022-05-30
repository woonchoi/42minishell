/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasong <jasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 23:50:54 by woonchoi          #+#    #+#             */
/*   Updated: 2022/05/30 18:32:46 by jasong           ###   ########.fr       */
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
		//변수 초기화
		info->error = 0;
		info->tinfo.qstatus = -1;
		info->index = 0;
		info->tinfo.tokenlist = NULL;
		lexer(info);
		free(info->input);
	}
}
