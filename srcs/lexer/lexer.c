/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:26:37 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/06 15:25:15 by woonchoi         ###   ########.fr       */
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
		printf("| token == %s", cur->token);
		printf("| token_origin == %s\n", cur->token_origin);
		cur = cur->next;
		++i;
	}
	printf("current pipe count = %d\n", info->cmd_count);
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
