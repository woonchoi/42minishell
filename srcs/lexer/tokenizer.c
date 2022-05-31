/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:37:58 by woonchoi          #+#    #+#             */
/*   Updated: 2022/05/31 20:26:59 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tokenizer(t_mshell_info *info)
{
	char	*token;
	t_token_info	*tinfo;

	token = NULL;
	tinfo = &info->tinfo;
	tinfo->qstatus = get_qstatus(info->input[info->index], tinfo->qstatus);
	if (tinfo->qstatus == NO_Q &&
		is_in_charset(info->input[info->index], SEPLIST))
	{
		if (info->input[info->index] == PIPE)
			tinfo->tokenlist = token_add_back(tinfo->tokenlist, PIPE, "|");
		else
			redirection_add_back(info);
	}
	string_add_back(info);
}
