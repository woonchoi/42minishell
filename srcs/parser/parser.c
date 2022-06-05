/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:12:52 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/05 12:45:35 by woonchoi         ###   ########.fr       */
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
	info->head = (t_tree_list *)calloc(pipecount, pipesize);
	if (!pipecount)
	{
		info->error = TRUE;
		safety_free(info->head);
	}
}



void	build_tree(t_mshell_info *info)
{
	init_tree_with_pipecount(info);
	if (info->error)
		return ;
	//need to make function
}

void	parser(t_mshell_info *info)
{
	if (info->error)
		return ;
}