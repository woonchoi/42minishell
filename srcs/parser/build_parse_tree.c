/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parse_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:01:11 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/13 15:03:05 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_redirection(t_token *cur, t_parse_util *par_v, t_info *info)
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

void	build_cmd_arg(t_token *cur, t_parse_util *par_v, t_info *info)
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

void	build_tree_with_token(t_token **cur, t_tree *root, t_info *info)
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
	info->heredoc_count = par_v.heredoc_count;
}

void	build_tree(t_info *info)
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
		build_tree_with_token(&cur, info->tree[i].root, info);
		printf("\n");
		print_tree_result(info->tree[i].root);
	}
}
