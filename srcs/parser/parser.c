/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:12:52 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/06 20:55:37 by woonchoi         ###   ########.fr       */
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
	info->tree = (t_tree_list *)ft_calloc(pipecount, pipesize);
	if (!info->tree)
	{
		info->error = TRUE;
		safety_free(info->tree);
	}
}

t_tree	*create_node(int type, char *token, t_mshell_info *info)
{
	t_tree	*node;

	node = (t_tree *)ft_calloc(1, sizeof(t_tree));
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
	par_v->cmd_status = FALSE;
	par_v->red_status = FALSE;
	par_v->heredoc_status = FALSE;
}

void	add_red_node(t_tree **parent, char *s, int t, t_mshell_info *info)
{
	if ((*parent)->type == ROOT)
	{
		(*parent)->l_child = create_node(BRANCH, "reds branch", info);
		(*parent) = (*parent)->l_child;
		(*parent)->l_child = create_node(BRANCH, "single red branch", info);
		(*parent)->l_child->l_child = create_node(t, s, info);
	}
	else
	{
		(*parent)->r_child = create_node(BRANCH, "reds branch", info);
		(*parent) = (*parent)->r_child;
		(*parent)->l_child = create_node(BRANCH, "single red branch", info);
		(*parent)->l_child->l_child = create_node(t, s, info);
	}

}

void	build_redirection(t_token *cur, t_parse_util *par_v, t_mshell_info *info)
{
	if (cur->tokentype == HEREDOC)
	{
		par_v->heredoc_status = TRUE;
		par_v->heredoc_count++;
	}
	else
		par_v->red_status = TRUE;
	add_red_node(&par_v->red_cur, cur->token, cur->tokentype, info);
}

void	add_arg_node(t_tree **parent, char *s, int t, t_mshell_info *info)
{
	(*parent)->l_child->r_child = create_node(t, s, info);
}

void	add_cmd_node(t_tree **parent, char *s, int t, t_mshell_info *info)
{
	(*parent)->r_child = create_node(BRANCH, "cmd branch", info);
	(*parent) = (*parent)->r_child;
	(*parent)->l_child = create_node(t, s, info);
}

void	add_cmd_arg(t_tree **parent, char *s, t_mshell_info *info)
{
	char *temp;

	if ((*parent)->type == BRANCH)
	{
		(*parent)->r_child = create_node(OPTARG, s, info);
		(*parent) = (*parent)->r_child;
	}
	else if ((*parent)->type == OPTARG)
	{
		temp = (*parent)->token;
		(*parent)->token = ft_strjoin((*parent)->token, " ");
		safety_free(temp);
		temp = (*parent)->token;
		(*parent)->token = ft_strjoin((*parent)->token, s);
		safety_free(temp);
	}
}

void	build_cmd_arg(t_token *cur, t_parse_util *par_v, t_mshell_info *info)
{
	if (par_v->heredoc_status)
	{
		add_arg_node(&par_v->red_cur, cur->token_origin, OPTARG, info);
		par_v->heredoc_status = FALSE;
	}
	else if (par_v->red_status)
	{
		add_arg_node(&par_v->red_cur, cur->token, OPTARG, info);
		par_v->red_status = FALSE;
	}
	else if (!par_v->cmd_status)
	{
		add_cmd_node(&par_v->cmd_cur, cur->token, CMD, info);
		par_v->cmd_status = TRUE;
	}
	else
		add_cmd_arg(&par_v->cmd_cur, cur->token, info);
}

void	build_tree_with_token(t_token **cur, t_tree *root, t_mshell_info *info)
{
	t_parse_util	par_v;

	init_parse_util(&par_v, root);
	while ((*cur))
	{
		if ((*cur)->tokentype == PIPE)
		{
			(*cur) = (*cur)->next;
			break ;
		}
		else if (is_redirection((*cur)->tokentype))
			build_redirection((*cur), &par_v, info);
		else if ((*cur)->tokentype == NORMAL)
			build_cmd_arg((*cur), &par_v, info);
		(*cur) = (*cur)->next;
	}
}

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

void	build_tree(t_mshell_info *info)
{
	t_token	*cur;
	int		i;

	cur = info->tinfo.tokenlist;
	i = -1;
	init_tree_with_pipecount(info);
	if (info->error)
		return ;
	while (++i < info->cmd_count + 1)
	{
		printf("PIPE NUMBER : %d \n\n", i);
		info->tree[i].root = create_node(ROOT, "root", info);
		build_tree_with_token(&cur, info->tree[i].root, info);
		print_tree_result(info->tree[i].root);
		printf("\n");
	}
}

void	parser(t_mshell_info *info)
{
	if (info->error)
		return ;
	build_tree(info);
}