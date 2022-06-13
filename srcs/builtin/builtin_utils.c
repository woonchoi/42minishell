/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasong <jasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:08:45 by jasong            #+#    #+#             */
/*   Updated: 2022/06/13 18:54:34 by jasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_two_arg(void *arg1, void *arg2)
{
	free(arg1);
	free(arg2);
}

t_env_list	*new_env_list(char *argv)
{
	t_env_list	*new;
	char		*sep;

	new = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new)
		return (NULL);
	sep = ft_strchr(argv, '=');
	new->key = ft_strndup(argv, sep - argv);
	if (!new->key[0])
	{
		free_two_arg(new->key, new);
		return (NULL);
	}
	new->value = ft_strdup(sep + 1);
	if (!new->value || !check_avaliable_key(new->key))
	{
		if (new->value)
			free(new->value);
		free_two_arg(new->key, new);
		return (NULL);
	}
	new->split_value = ft_split(sep + 1, ':');
	new->next = NULL;
	return (new);
}

void	env_add_back(t_env_list **env_list, t_env_list *new)
{
	t_env_list	*cur;

	if (!*env_list)
		*env_list = new;
	else
	{
		cur = *env_list;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}

void	update_env_val(t_env_list *key_loc, char *sep, int del)
{
	char	*new_value;

	if (!key_loc)
		return ;
	if (del == '+')
		new_value = ft_strdup(sep + 2);
	else if (del == '=')
		new_value = ft_strdup(sep + 1);
	free(key_loc->value);
	free_split_value(key_loc->split_value);
	key_loc->value = new_value;
	key_loc->split_value = ft_split(new_value, ':');
}

t_env_list	*env_key_location(t_env_list *env_head, char *key)
{
	int	key_len;

	key_len = ft_strlen(key);
	while (env_head)
	{
		if (!ft_strncmp(env_head->key, key, key_len + 1))
			return (env_head);
		env_head = env_head->next;
	}
	return (NULL);
}
