/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:12:52 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/02 21:20:26 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_noquote_dollar_in_str(char *token)
{
	int	qstatus;
	int	i;

	qstatus = NO_Q;
	i = 0;
	while (token[i])
	{
		qstatus = get_qstatus(token[i], qstatus);
		if (qstatus == NO_Q && token[i] == '$')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	init_expand_token_value(t_expand_token *exp_v)
{
	exp_v->str1 = NULL;
	exp_v->str2 = NULL;
	exp_v->i = 0;
	exp_v->j = 0;
	exp_v->qstatus = NO_Q;
}

int	check_dollar_critical_case(char *token, int qstatus)
{
	if (ft_strlen(token) == 1
		|| !ft_strncmp(token, "$$", 2)
		|| (!ft_strncmp(token, "$\"", 2) && qstatus == DOUBLE_Q)
		|| (!ft_strncmp(token, "$\'", 2) && qstatus == DOUBLE_Q))
		return (TRUE);
	return (FALSE);
}

char	*get_key_in_token(char *token)
{
	int		i;
	char	*key;

	i = 1;
	key = NULL;
	if (ft_isdigit(token[i]))
		return (key);
	while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
		i++;
	key = ft_strndup(&token[1], i - 1);
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

char	*expand_envvars(char *token, t_expand_token *exp_v, t_env_list *env)
{
	char	*key;
	char	*value;
	int		i;

	i = exp_v->i;
	if (check_dollar_critical_case(token, exp_v->qstatus))
	{
		exp_v->str1 = ft_strjoin(exp_v->str1, "$");
		exp_v->i++;
		exp_v->j = exp_v->i;
		return (exp_v->str1);
	}
	key = get_key_in_token(token);
	value = get_value_with_key(key, env);
	if (!ft_strlen(key))
		exp_v->i += 1;
	exp_v->i += ft_strlen(key);
	if (token[exp_v->i - i] != DOUBLE_Q && token[exp_v->i - i] != SINGLE_Q)
		exp_v->j = exp_v->i + 1;
	else
		exp_v->j = exp_v->i;
	if (value)
		exp_v->str1 = ft_strjoin(exp_v->str1, value);
	return (exp_v->str1);
}

char	*expand_token_envvars(char *token, t_env_list *env)
{
	t_expand_token	exp_v;

	init_expand_token_value(&exp_v);
	if (!is_noquote_dollar_in_str(token))
		return (NULL);
	while (token[exp_v.i])
	{
		exp_v.qstatus = get_qstatus(token[exp_v.i], exp_v.qstatus);
		if (exp_v.qstatus == NO_Q && token[exp_v.i] ==  '$')
		{
			exp_v.str2 = ft_strndup(&token[exp_v.j], exp_v.i - exp_v.j);
			exp_v.str1 = ft_strjoin(exp_v.str1, exp_v.str2);
			exp_v.str1 = expand_envvars(&token[exp_v.i], &exp_v, env);
		}
		exp_v.i++;
	}
	exp_v.str2 = ft_strndup(&token[exp_v.j], exp_v.i - exp_v.j);
	return (ft_strjoin(exp_v.str1, exp_v.str2));
}

void	expand_tokens_envvars(t_token *cur, t_env_list *env)
{
	char	*new_token;
	char	*temp;

	temp = cur->token;
	if (cur->tokentype = NORMAL)
	{
		new_token = expand_token_envvars(cur->token, env);
		if (new_token)
		{
			temp = cur->token;
			cur->token = new_token;
		}
	}
}

void	expand_noquote_envvars(t_mshell_info *info)
{
	t_token	*cur;

	cur = info->tinfo.tokenlist;
	while (cur)
	{
		expand_tokens_envvars(cur, info->env_head);
		cur = cur->next;
	}
}

void	parser(t_mshell_info *info)
{
	if (info->error)
		return ;
	expand_noquote_envvars(info);
}