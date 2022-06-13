/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preorder_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:49:48 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/13 17:34:07 by woonchoi         ###   ########.fr       */
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
		if (!node->l_child->token)
			return ;
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