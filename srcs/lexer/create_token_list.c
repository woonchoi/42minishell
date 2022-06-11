/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:58:01 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/11 19:13:38 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(int type, char *str)
{
	t_token	*ret;

	ret = ft_calloc(1, sizeof(t_token));
	if (!ret)
		return (NULL);
	ret->tokentype = type;
	ret->token = ft_strdup(str);
	ret->token_origin = ft_strdup(str);
	ret->next = NULL;
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
		cur = token;
		while (cur->next)
			cur = cur->next;
		cur->next = new_token;
	}
	return (token);
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
		if ((is_in_charset(info->input[i], SEPLIST)
			|| is_in_charset(info->input[i], SPACELIST)) && tinfo->qstatus == NO_Q)
			break ;
		i++;
		tinfo->qstatus = get_qstatus(info->input[i], tinfo->qstatus);
	}
	temp = ft_strndup(&info->input[info->index], i - info->index);
	printf("current string : |%s|\n", temp);
	str = ft_strtrim(temp, SPACELIST);
	printf("trim data : |%s|\n", str);
	safety_free(temp);
	if (i != info->index)
		info->index = i - 1;
	if (!is_only_space(str))
		tinfo->tokenlist = token_add_back(tinfo->tokenlist, NORMAL, str);
	safety_free(str);
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
