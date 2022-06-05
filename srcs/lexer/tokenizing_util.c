/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:23:44 by woonchoi          #+#    #+#             */
/*   Updated: 2022/05/31 20:24:29 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_qstatus(char c, int qstatus)
{
	if (qstatus == NO_Q)
	{
		if (c == SINGLE_Q)
			qstatus = SINGLE_Q;
		else if (c == DOUBLE_Q)
			qstatus = DOUBLE_Q;
	}
	else if (qstatus == SINGLE_Q)
	{
		if (c == SINGLE_Q)
			qstatus = NO_Q;
	}
	else if (qstatus == DOUBLE_Q)
	{
		if (c == DOUBLE_Q)
			qstatus = NO_Q;
	}
	return (qstatus);
}

int	check_quote(t_mshell_info *info)
{
	int	i;

	i = 0;
	while (info->input && info->input[i])
	{
		info->tinfo.qstatus = get_qstatus(info->input[i], info->tinfo.qstatus);
		i++;
	}
	if (info->tinfo.qstatus != NO_Q)
	{
		info->error = TRUE;
		ft_putstr_fd("bash : Unclosed quote found\n", 2);
	}
	return (info->error);
}

int	is_in_charset(char c, const char *charset)
{
	int i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	is_only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_in_charset(str[i], SPACELIST))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int		is_redirection(int tokentype)
{
	if (tokentype == INPUT_R
		|| tokentype == OUTPUT_R
		|| tokentype == APPEND_R
		|| tokentype == HEREDOC)
		return (TRUE);
	return (FALSE);
}
