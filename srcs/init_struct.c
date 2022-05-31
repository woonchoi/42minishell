/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:33:44 by woonchoi          #+#    #+#             */
/*   Updated: 2022/05/31 20:39:29 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_prompt_cycle(t_mshell_info *info)
{
	info->error = 0;
	info->index = 0;
	info->tinfo.qstatus = 0;
	info->tinfo.tokenlist = 0;
	info->head = NULL;
	info->cmd_count = 0;
	info->input = 0;
}

void	init_mshell_info(t_mshell_info *info)
{
	info->head = NULL;
	info->env_head = NULL;
	info->cmd_count = 0;
	info->input = NULL;
	info->error = 0;
	info->index = 0;
}
