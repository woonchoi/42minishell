/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envvars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:27:08 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/15 15:13:04 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_question(t_expand_token *exp_v)
{
	char	*temp;

	temp = exp_v->str1;
	exp_v->str1 = ft_strjoin(exp_v->str1, ft_itoa(g_exit_status));
	exp_v->i++;
	exp_v->j = exp_v->i + 1;
	safety_free((void **)&temp);
}

void	expand_critical_case(t_expand_token *exp_v)
{
	char	*temp;

	temp = exp_v->str1;
	exp_v->str1 = ft_strjoin(exp_v->str1, "$");
	exp_v->j = exp_v->i + 1;
	if (temp)
		safety_free((void **)&temp);
}

void	expand_remain_string(char *token, t_expand_token *exp_v)
{
	char	*temp;

	temp = exp_v->str1;
	exp_v->str1 = ft_strjoin(exp_v->str1, &token[exp_v->j]);
	safety_free((void **)&temp);
}

void	expand_envvars(char *token, t_expand_token *exp_v, t_env_list *env)
{
	char	*key;
	char	*value;
	char	*temp;

	if (check_dollar_next_question(token, exp_v))
		expand_question(exp_v);
	else if (check_dollar_critical_case(token, exp_v->qstatus))
		expand_critical_case(exp_v);
	else
	{
		temp = exp_v->str1;
		key = get_key_in_token(token, exp_v);
		value = get_value_with_key(key, env);
		if (value)
		{
			exp_v->str1 = ft_strjoin(exp_v->str1, value);
			safety_free((void **)&temp);
		}
		if (!ft_strlen(key))
			exp_v->i += 1;
		exp_v->i += ft_strlen(key);
		exp_v->j = exp_v->i + 1;
		safety_free((void **)&key);
		safety_free((void **)&value);
	}
}
