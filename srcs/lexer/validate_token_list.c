/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_token_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:59:15 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/16 16:56:14 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	check_pipe_is_next(t_token *token)
{
	if (token->tokentype == PIPE)
	{
		ft_putstr_fd(SYNTAX_ERROR_PRE, STDERR_FILENO);
		ft_putstr_fd("|'\n", STDERR_FILENO);
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
		ft_putstr_fd(SYNTAX_ERROR_PRE, 2);
		ft_putstr_fd(temp, 2);
		ft_putstr_fd("'\n", 2);
		return (TRUE);
	}
	return (FALSE);
}	

void	check_metachar_next_null(t_info *info, t_token *token)
{
	if (is_redirection(token->tokentype))
	{
		ft_putstr_fd(SYNTAX_ERROR_PRE, STDERR_FILENO);
		ft_putstr_fd("newline'\n", STDERR_FILENO);
		info->error = TRUE;
		g_exit_status = 2;
	}
	else if (token->tokentype == PIPE)
	{
		ft_putstr_fd(SYNTAX_ERROR_PRE, STDERR_FILENO);
		ft_putstr_fd("|'\n", STDERR_FILENO);
		info->error = TRUE;
		g_exit_status = 2;
	}
}

void	validate_syntax(t_info *info)
{
	t_token	*tokenlist;

	tokenlist = info->tinfo.tokenlist;
	while (!info->error && tokenlist && tokenlist->next)
	{
		if (is_redirection(tokenlist->tokentype))
		{
			if (check_pipe_is_next(tokenlist->next))
				info->error = TRUE;
			if (check_redirection_is_next(tokenlist->next))
				info->error = TRUE;
		}
		else if (tokenlist->tokentype == PIPE)
		{
			if (check_pipe_is_next(tokenlist->next))
				info->error = TRUE;
		}
		tokenlist = tokenlist->next;
		if (info->error == TRUE)
			g_exit_status = 2;
	}
	if (!info->error)
		check_metachar_next_null(info, tokenlist);
}
