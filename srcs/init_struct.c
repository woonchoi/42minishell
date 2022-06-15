/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:33:44 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/15 14:20:20 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_prompt_cycle(t_info *info)
{
	info->error = FALSE;
	info->index = 0;
	info->tinfo.qstatus = NO_Q;
	info->tinfo.tokenlist = NULL;
	info->tree = NULL;
	info->cmd_count = 1;
	info->input = NULL;
}
