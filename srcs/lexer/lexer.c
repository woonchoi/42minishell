/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:26:37 by woonchoi          #+#    #+#             */
/*   Updated: 2022/05/31 20:49:35 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_lexer_result(t_mshell_info *info)
{
	t_token *cur;
	int		i;

	cur = info->tinfo.tokenlist;
	i = 1;
	while (cur)
	{
		printf("current index : %d", i);
		printf("| token_type == %d ", cur->tokentype);
		printf("| token == %s\n", cur->token);
		cur = cur->next;
		++i;
	}
}

void	lexer(t_mshell_info *info)
{
	if (info->error)
		return ;
	if (check_quote(info))
		return ;
	while (info->input[info->index])
	{
		printf("%s\n", &info->input[info->index]);
		tokenizer(info);
		info->index++;
	}
	if (!info->tinfo.tokenlist)
	{
		info->error = TRUE;
		return ;
	}
	print_lexer_result(info);
	validate_syntax(info);
}
