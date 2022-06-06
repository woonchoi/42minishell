/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:34:06 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/06 14:30:03 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_expand_token_value(t_expand_token *exp_v)
{
	exp_v->str1 = NULL;
	exp_v->str2 = NULL;
	exp_v->i = 0;
	exp_v->j = 0;
	exp_v->qstatus = NO_Q;
}

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

void	expand_question(t_expand_token *exp_v)
{
	int		test_exit_status;
	char	*temp;

	test_exit_status = 0;
	temp = exp_v->str1;
	exp_v->str1 = ft_strjoin(exp_v->str1, ft_itoa(test_exit_status));
	exp_v->i++;
	exp_v->j = exp_v->i + 1;
	safety_free(temp);
}

char	*get_key_in_token(char *token, t_expand_token *exp_v)
{
	int		i;
	char	*key;

	i = exp_v->i + 1;
	key = NULL;
	if (ft_isdigit(token[i]))
		return (key);
	while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
		i++;
	key = ft_strndup(&token[exp_v->i + 1], i - exp_v->i - 1);
	return (key);
}

char	*get_value_with_key(char *key, t_env_list *env)
{
	char	*value;

	value = NULL;
	while (env)
	{
		if (ft_strlen(key) == ft_strlen(env->key)
			&& !ft_strncmp(key, env->key, ft_strlen(key)))
		{
			value = (ft_strdup(env->value));
			break ;
		}
		env = env->next;
	}
	return (value);
}

int	check_dollar_critical_case(char *token, int i, int qstatus)
{
	if (ft_strlen(token) == 1
		|| (!ft_strncmp(token, "$\"", 2) && qstatus == DOUBLE_Q)
		|| (!ft_strncmp(token, "$\'", 2) && qstatus == DOUBLE_Q))
		return (TRUE);
	return (FALSE);
}

void	expand_critical_case(t_expand_token *exp_v)
{
	char *temp;

	temp = exp_v->str1;
	exp_v->str1 = ft_strjoin(exp_v->str1, "$");
	exp_v->j = exp_v->i + 1;
	if (temp)
		safety_free(temp);
}

void	expand_envvars(char *token, t_expand_token *exp_v, t_env_list *env)
{
	char	*key;
	char	*value;
	char	*temp;

	if (check_dollar_next_question(token, exp_v))
		expand_question(exp_v);
	else if (check_dollar_critical_case(token, exp_v->i, exp_v->qstatus))
		expand_critical_case(exp_v);
	else
	{
		temp = exp_v->str1;
		key = get_key_in_token(token, exp_v);
		value = get_value_with_key(key, env);
		if (value)
		{
			exp_v->str1 = ft_strjoin(exp_v->str1, value);
			safety_free(temp);
		}
		if (!ft_strlen(key))
			exp_v->i += 1;
		exp_v->i += ft_strlen(key);
		exp_v->j = exp_v->i + 1;
		safety_free(key);
		safety_free(value);
	}
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

void	save_current_string(char *token, t_expand_token *exp_v)
{
	char	*temp;

	temp = exp_v->str1;
	exp_v->str2 = ft_strndup(&token[exp_v->j], exp_v->i - exp_v->j);
	exp_v->str1 = ft_strjoin(exp_v->str1, exp_v->str2);
	free(temp);
	exp_v->j = exp_v->i + 1;
}

void	expand_remain_string(char *token, t_expand_token *exp_v)
{
	char	*temp;

	temp = exp_v->str1;
	exp_v->str1 = ft_strjoin(exp_v->str1, &token[exp_v->j]);
	safety_free(temp);
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
	if (exp_v.i != exp_v.j + 1)
		expand_remain_string(token, &exp_v);
	return (exp_v.str1);
}

char	*delete_quote(char *token)
{
	t_expand_token	exp_v;
	char	*new_token;

	init_expand_token_value(&exp_v);
	new_token = NULL;
	while (token[exp_v.i])
	{
		exp_v.qstatus = get_qstatus(token[exp_v.i], exp_v.qstatus);
		if (check_quote_need_delete(token[exp_v.i], &exp_v))
			save_current_string(token, &exp_v);
		exp_v.i++;
	}
	if (exp_v.i != exp_v.j + 1)
		expand_remain_string(token, &exp_v);
	return (exp_v.str1);
}

void	expand_token(t_token *cur, t_env_list *env)
{
	char	*temp;

	temp = cur->token;
	if (!find_ds_need_expand(cur->token))
	{
		cur->token = delete_quote(cur->token);
		safety_free(temp);
		return ; 
	}
	cur->token = create_expand_result(cur->token, env);
	safety_free(temp);
}

void	expand_tokens(t_mshell_info *info)
{
	t_token	*cur;

	cur = info->tinfo.tokenlist;
	while (cur)
	{
		expand_token(cur, info->env_head);
		cur = cur->next;
	}
}

void	scanner(t_mshell_info *info)
{
	if (info->error)
		return ;
	expand_tokens(info);
}