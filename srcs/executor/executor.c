/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:11:58 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/13 17:34:34 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_info *info)
{
	int	in;
	int	out;
	int	i;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	i = -1;
	if (no_fork_cmd(info->tree[0].root) && info->cmd_count == 1)
		preorder_once(info, info->tree[0].root, in, out);
	// else
	// 	preorder_general(info, in, out);
}

void	executor(t_info *info)
{
	if (info->error == TRUE)
		return ;
	heredoc_process(info);
	execute(info);
}
