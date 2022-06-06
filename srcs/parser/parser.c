/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:12:52 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/06 15:28:01 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_tree_with_pipecount(t_mshell_info *info)
{
	int	pipecount;
	int	pipesize;

	if (info->error)
		return ;
	pipecount = info->cmd_count + 2;
	pipesize = sizeof(t_tree_list);
	info->tree = (t_tree_list *)calloc(pipecount, pipesize);
	if (!info->tree)
	{
		info->error = TRUE;
		safety_free(info->tree);
	}
}

t_tree	*create_node(int type, char *token, t_mshell_info *info)
{
	t_tree	*node;

	node = (t_tree *)calloc(1, sizeof(t_tree));
	if (!node)
	{
		info->error = TRUE;
		return (NULL);
	}
	node->type = type;
	node->token = ft_strdup(token);
	return (node); 
}

void	init_parse_util(t_parse_util *par_v, t_tree *root)
{
	par_v->red_cur = root;
	par_v->cmd_cur = root;
	par_v->temp = NULL;
	par_v->cmd_status = 0;
	par_v->red_status = 0;
}

void	build_tree_with_token(t_token *cur, t_tree *root)
{
	t_parse_util	par_v;

	init_parse_util(&par_v, root);
	while (cur)
	{
		if (cur->tokentype = PIPE)
			break ;
		if (cur->tokentype = NORMAL)
	}
}

void	build_tree(t_mshell_info *info)
{
	t_token	*cur;
	int		i;

	cur = info->tinfo.tokenlist;
	i = -1;
	init_tree_with_pipecount(info);
	if (info->error)
		return ;
	while (++i < info->cmd_count)
	{
		info->tree[i].root = create_node(ROOT, "root", info);
		build_tree_with_token(cur, info->tree[i].root)
	}
}

void	parser(t_mshell_info *info)
{
	if (info->error)
		return ;
}