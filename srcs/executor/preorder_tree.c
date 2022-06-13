/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preorder_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:49:48 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/13 18:32:59 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	preorder(t_info *info, t_tree *node)
{
	if (!node)
		return ;
	if (node->l_child && is_redirection(node->l_child->type))
	{
		g_exit_status = execute_redirection(info, node);
		if (g_exit_status)
			return ;
	}
	if (node->l_child && node->l_child->type == CMD)
	{
		if (execute_cmd(info, node))
			return ;
	}
	preorder(info, node->l_child);
	preorder(info, node->r_child);
}

void	preorder_once(t_info *info, t_tree *node, int in, int out)
{
	preorder(info, node);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
}

void	preorder_general(t_info *info, int in, int out)
{
	int	i;

	i = -1;
	while (++i < info->cmd_count)
	{
		if (i < info->cmd_count)
		{
			pipe(info->tree[i].fd);
			info->tree[i + 1].prev_fd = dup(info->tree[i].fd[0]);
			close(info->tree[i].fd[0]);
		}
		fork_cmd(info, i, in, out);
	}
	g_exit_status = check_exit_status(info);
}
