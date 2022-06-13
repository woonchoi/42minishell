/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:22:44 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/13 13:01:26 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_current_string(char *token, t_expand_token *exp_v)
{
	char	*temp;

	temp = exp_v->str1;
	exp_v->str2 = ft_strndup(&token[exp_v->j], exp_v->i - exp_v->j);
	exp_v->str1 = ft_strjoin(exp_v->str1, exp_v->str2);
	free(temp);
	exp_v->j = exp_v->i + 1;
}

char	*create_expand_result(char *token, t_env_list *env)
{
	t_expand_token	exp_v;

	init_expand_token_value(&exp_v);
	while (token[exp_v.i])
	{
		exp_v.qstatus = get_qstatus(token[exp_v.i], exp_v.qstatus);
		if (check_quote_need_delete(token[exp_v.i], &exp_v))
			save_current_string(token, &exp_v);
		else if ((exp_v.qstatus == NO_Q || exp_v.qstatus == DOUBLE_Q)
			&& token[exp_v.i] == '$')
		{
			preprocess_expand_ds(token, &exp_v);
			expand_envvars(token, &exp_v, env);
		}
		exp_v.i++;
	}
	if (exp_v.i != exp_v.j)
		expand_remain_string(token, &exp_v);
	return (exp_v.str1);
}

char	*delete_quote(char *token)
{
	t_expand_token	exp_v;
	char			*new_token;

	init_expand_token_value(&exp_v);
	new_token = NULL;
	while (token[exp_v.i])
	{
		exp_v.qstatus = get_qstatus(token[exp_v.i], exp_v.qstatus);
		if (check_quote_need_delete(token[exp_v.i], &exp_v))
			save_current_string(token, &exp_v);
		exp_v.i++;
	}
	if (exp_v.i != exp_v.j)
		expand_remain_string(token, &exp_v);
	return (exp_v.str1);
}

void	expand_token(t_token *cur, t_env_list *env)
{
	char	*temp;
	char	*temp_origin;

	temp = cur->token;
	temp_origin = cur->token_origin;
	if (cur->tokentype == NORMAL)
	{
		cur->token_origin = delete_quote(cur->token_origin);
		safety_free(temp_origin);
		if (!find_ds_need_expand(cur->token))
		{
			cur->token = delete_quote(cur->token);
			safety_free(temp);
			return ;
		}
		cur->token = create_expand_result(cur->token, env);
		safety_free(temp);
	}
}

void	expand_tokens(t_info *info)
{
	t_token	*cur;

	cur = info->tinfo.tokenlist;
	while (cur)
	{
		expand_token(cur, info->env_head);
		cur = cur->next;
	}
}
