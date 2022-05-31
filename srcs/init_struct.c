/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:33:44 by woonchoi          #+#    #+#             */
/*   Updated: 2022/05/31 20:44:10 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_prompt_cycle(t_mshell_info *info)
{
	info->error = 0;
	info->index = 0;
	info->tinfo.qstatus = -1;
	info->tinfo.tokenlist = 0;
	info->head = NULL;
	info->cmd_count = 0;
	info->input = 0;
}
