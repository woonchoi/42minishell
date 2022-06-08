/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:23:41 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/08 19:24:31 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_ds_need_expand(char *token)
{
	int	qstatus;

	qstatus = NO_Q;
	while (*token)
	{
		qstatus = get_qstatus(*token, qstatus);
		if ((qstatus == NO_Q || qstatus == DOUBLE_Q) && *token == '$')
			return (TRUE);
		token++;
	}
	return (FALSE);
}

void	preprocess_expand_ds(char *token, t_expand_token *exp_v)
{
	char	*temp;

	temp = exp_v->str1;
	exp_v->str2 = ft_strndup(&token[exp_v->j], exp_v->i - exp_v->j);
	exp_v->str1 = ft_strjoin(exp_v->str1, exp_v->str2);
	safety_free(temp);
	safety_free(exp_v->str2);
	exp_v->str2 = NULL;
}

int	check_dollar_next_question(char *token, t_expand_token *exp_v)
{
	if (token[exp_v->i + 1] == '?')
		return (TRUE);
	return (FALSE);
}

int	check_dollar_critical_case(char *token, int i, int qstatus)
{
	if (ft_strlen(token) == 1
		|| (!ft_strncmp(token, "$\"", 2) && qstatus == DOUBLE_Q)
		|| (!ft_strncmp(token, "$\'", 2) && qstatus == DOUBLE_Q))
		return (TRUE);
	return (FALSE);
}

int	check_quote_need_delete(char c, t_expand_token *exp_v)
{
	if (exp_v->qstatus == NO_Q || exp_v->qstatus == DOUBLE_Q)
	{
		if (c == '\"')
			return (TRUE);
	}
	if (exp_v->qstatus == NO_Q || exp_v->qstatus == SINGLE_Q)
	{
		if (c == '\'')
			return (TRUE);
	}
	return (FALSE);
}
