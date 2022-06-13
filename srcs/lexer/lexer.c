/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:26:37 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/13 14:55:12 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer(t_info *info)
{
	if (check_quote(info))
		return ;
	while (info->input[info->index])
	{
		tokenizer(info);
		info->index++;
	}
	if (!info->tinfo.tokenlist)
	{
		info->error = TRUE;
		return ;
	}
	validate_syntax(info);
}
