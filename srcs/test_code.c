/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:08:49 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/13 15:03:34 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_list(t_info *info)
{
	t_env_list	*env_list;
	int			i;

	env_list = info->env_head;
	while (env_list)
	{
		printf("key : %s\n", env_list->key);
		printf("value : %s\n", env_list->value);
		i = 0;
		while (env_list->split_value[i])
		{
			printf("value(index %d) : %s\n", i, env_list->split_value[i]);
			i++;
		}
		env_list = env_list->next;
	}
}

void	print_lexer_result(t_info *info)
{
	t_token *cur;
	int		i;

	cur = info->tinfo.tokenlist;
	i = 1;
	while (cur)
	{
		printf("current index : %d", i);
		printf("| token_type == %d ", cur->tokentype);
		printf("| token == %s", cur->token);
		printf("| token_origin == %s\n", cur->token_origin);
		cur = cur->next;
		++i;
	}
	printf("current pipe count = %d\n", info->cmd_count);
}

void	print_tree_preorder(t_tree *node)
{
	if (node)
	{
		printf("current node type : %d | current node data : %s\n", node->type, node->token);
		print_tree_preorder(node->l_child);
		print_tree_preorder(node->r_child);
	}
}

void	print_tree_result(t_tree *root)
{
	print_tree_preorder(root);
}
