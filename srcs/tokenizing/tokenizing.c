/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:37:58 by woonchoi          #+#    #+#             */
/*   Updated: 2022/05/28 21:45:01 by woonchoi         ###   ########.fr       */
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
	else if (qstatus = SINGLE_Q)
	{
		if (c == SINGLE_Q)
			qstatus = NO_Q;
	}
	else if (qstatus = DOUBLE_Q)
	{
		if (c == DOUBLE_Q)
			qstatus = NO_Q;
	}
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
		ft_putstr_fd("bash : Unclosed quote found", 2);
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

t_token	*create_token(int type, char *str)
{
	t_token	*ret;

	ret = ft_calloc(1, sizeof(t_token));
	if (!ret)
		return (NULL);
	ret->tokentype = type;
	ret->token = ft_strdup(str);
	ret->next = NULL;
	ret->prev = NULL;
	return (ret);
}

t_token	*token_add_back(t_token *token, int type, char *str)
{
	t_token	*new_token;
	t_token	*cur;

	new_token = create_token(type, str);
	if (!new_token)
		return (NULL);
	if (!token)
		return (new_token);
	else
	{
		cur = new_token;
		while (cur->next)
			cur = cur->next;
		cur->next = new_token;
		new_token->prev = cur;
	}
	return (token);
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

void	string_add_back(t_mshell_info *info)
{
	int				i;
	char			*temp;
	char			*str;
	t_token_info	*tinfo;

	i = info->index;
	tinfo = &info->tinfo;
	while (info->input[i])
	{
		if (is_in_charset(info->input[i], SEPLIST) && tinfo->qstatus == NO_Q)
			break ;
		i++;
		tinfo->qstatus = get_qstatus(info->input[i], tinfo->qstatus);
	}
	temp = ft_strndup(&info->input[info->index], i - info->index);
	str = ft_strtrim(temp, SPACELIST);
	free(temp);
	if (i > 0)
		info->index += i - 1;
	if (!is_only_space(str))
		tinfo->tokenlist = token_add_back(tinfo->tokenlist, NORMAL, str);
	else
		free(str);
}

void	redirection_add_back(t_mshell_info *info)
{
	char			first_c;
	char			second_c;
	t_token_info	*tinfo;

	first_c = info->input[info->index];
	second_c = info->input[info->index + 1];
	tinfo = &info->tinfo;
	if (first_c == LEFT_ANGLE && second_c == LEFT_ANGLE)
	{
		tinfo->tokenlist = token_add_back(tinfo->tokenlist, HEREDOC, "<<");
		info->index++;
	}
	else if (first_c == RIGHT_ANGLE && second_c == RIGHT_ANGLE)
	{
		tinfo->tokenlist = token_add_back(tinfo->tokenlist, APPEND_R, ">>");
		info->index++;
	}
	else if (first_c == LEFT_ANGLE)
		tinfo->tokenlist = token_add_back(tinfo->tokenlist, INPUT_R, "<");
	else if (first_c == RIGHT_ANGLE)
		tinfo->tokenlist = token_add_back(tinfo->tokenlist, OUTPUT_R, ">");
}

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
			tinfo->tokenlist = token_add_back(token, PIPE, "|");
		else
			redirection_add_back(info);
	}
	string_add_back(info);
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
	if (token->tokentype == PIPE)
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
		temp == "<<";
	if (temp)
	{
		ft_putstr_fd("bash: unexpected token '", 2);
		ft_putstr_fd(temp, 2);
		ft_putstr_fd("detected\n", 2);
		return (TRUE);
	}
	return (FALSE;
}

void	validate_syntax(t_mshell_info *info)
{
	t_token	*tokenlist;

	tokenlist = info->tinfo.tokenlist;
	while (tokenlist)
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

void	lexer(t_mshell_info *info)
{
	if (info->error)
		return ;
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
