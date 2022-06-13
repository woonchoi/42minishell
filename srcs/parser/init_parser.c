/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:00:36 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/13 21:44:43 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_tree_with_pipecount(t_info *info)
{
	int	pipecount;
	int	pipesize;
	int	i;

	i = -1;
	if (info->error)
		return ;
	pipecount = info->cmd_count;
	pipesize = sizeof(t_tree_list);
	info->tree = (t_tree_list *)ft_calloc(pipecount, pipesize);
	if (!info->tree)
	{
		info->error = TRUE;
		safety_free(info->tree);
	}
	while (++i < pipecount)
		info->tree[i].prev_fd = -1;
}

void	init_parse_util(t_parse_util *par_v, t_tree *root)
{
	par_v->red_cur = root;
	par_v->cmd_cur = root;
	par_v->temp = NULL;
	par_v->cmd_status = FALSE;
	par_v->red_status = FALSE;
	par_v->heredoc_status = FALSE;
	par_v->heredoc_count = 0;
}
