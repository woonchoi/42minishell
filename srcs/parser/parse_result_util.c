/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_result_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:58:40 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/08 14:59:01 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	preorder_tree(t_tree *node)
{
	if (node)
	{
		printf("current node type : %d | current node data : %s\n", node->type, node->token);
		preorder_tree(node->l_child);
		preorder_tree(node->r_child);
	}
}

void	print_tree_result(t_tree *root)
{
	preorder_tree(root);
}
