/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:37:58 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/15 14:44:09 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(t_info *info)
{
	t_token_info	*tinfo;

	tinfo = &info->tinfo;
	tinfo->qstatus = get_qstatus(info->input[info->index], tinfo->qstatus);
	if (tinfo->qstatus == NO_Q
		&& ft_strchr(SEPLIST, info->input[info->index]))
	{
		if (info->input[info->index] == PIPE)
		{
			tinfo->tokenlist = token_add_back(tinfo->tokenlist, PIPE, "|");
			info->cmd_count++;
		}
		else
			redirection_add_back(info);
	}
	string_add_back(info);
}
