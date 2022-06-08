/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:14:58 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/08 12:14:32 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	iterate_free_tree(t_tree *node)
{
	t_tree	*l_child;
	t_tree	*r_child;

	if (!node)
		return ;
	l_child = node->l_child;
	r_child = node->r_child;
	safety_free(node->token);
	safety_free(node);
	iterate_free_tree(l_child);
	iterate_free_tree(r_child);
}

void	free_parse_tree(t_mshell_info *info)
{
	t_tree_list	*tree;
	int			i;
	
	tree = info->tree;
	if (!tree)
		return ;
	i = -1;
	while (++i < info->cmd_count + 1)
		iterate_free_tree(tree[i].root);
	safety_free(tree);
}

void	free_tokenlist(t_mshell_info *info)
{
	t_token	*cur;
	t_token	*temp;

	cur = info->tinfo.tokenlist;
	while (cur)
	{
		temp = cur;
		cur = cur->next;
		safety_free(temp->token);
		safety_free(temp->token_origin);
		safety_free(temp);
	}
}

void	terminate_free(t_mshell_info *info)
{
	free_tokenlist(info);
	free_parse_tree(info);
	safety_free(info->input);
	return ;
}