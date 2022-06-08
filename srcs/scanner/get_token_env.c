/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:26:08 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/08 19:31:15 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
