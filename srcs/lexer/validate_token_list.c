/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_token_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:59:15 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/11 19:32:02 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_pipe_is_next(t_token *token)
{
	if (token->tokentype == PIPE)
	{
		ft_putstr_fd("bash: unexpected token '|' detected\n", 2);
		return (TRUE);
	}
	return (FALSE);
}

int	check_null_is_next(t_token *token)
{
	if (!ft_strncmp(token->token, "", 1))
	{
		ft_putstr_fd("bash: unexpected token 'newline' detected\n", 2);
		return (TRUE);
	}
	return (FALSE);
}

int	check_redirection_is_next(t_token *token)
{
	char	*temp;

	temp = NULL;
	if (token->tokentype == INPUT_R)
		temp = "<";
	else if (token->tokentype == OUTPUT_R)
		temp = ">";
	else if (token->tokentype == APPEND_R)
		temp = ">>";
	else if (token->tokentype == HEREDOC)
		temp = "<<";
	if (temp)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		ft_putstr_fd(temp, 2);
		ft_putstr_fd("'\n", 2);
		return (TRUE);
	}
	return (FALSE);
}

void	validate_syntax(t_mshell_info *info)
{
	t_token	*tokenlist;

	tokenlist = info->tinfo.tokenlist;
	while (tokenlist && tokenlist->next)
	{
		if (is_redirection(tokenlist->tokentype))
		{
			if (check_pipe_is_next(tokenlist->next))
				info->error = TRUE;
			if (check_null_is_next(tokenlist->next))
				info->error = TRUE;
			if (check_redirection_is_next(tokenlist->next))
				info->error = TRUE;
		}
		else if (tokenlist->tokentype == PIPE)
		{
			if (check_pipe_is_next(tokenlist->next))
				info->error = TRUE;
			if (check_null_is_next(tokenlist->next))
				info->error = TRUE;
		}
		tokenlist = tokenlist->next;
		if (info->error == TRUE)
			return ;
	}
}