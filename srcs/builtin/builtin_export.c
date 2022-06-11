/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasong <jasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:10:41 by jasong            #+#    #+#             */
/*   Updated: 2022/06/11 13:50:26 by jasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define NO_DEL 0
#define ADD_VAL 1
#define ADD_ENV 2

t_env_list	*new_env_list(char *argv)
{
	t_env_list	*new;
	char		*sep;

	new = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new)
		return (NULL);
	sep = ft_strchr(argv, '=');
	new->key = ft_strndup(argv, sep - argv);
	if (!new->key)
	{
		free(new);
		return (NULL);
	}
	new->value = ft_strdup(sep + 1);
	if (!new->value || !check_avaliable_key(new->key))
	{
		if (new->value)
			free(new->value);
		free(new->key);
		free(new);
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

void	print_export_env(t_env_list *env_head)
{
	if (!env_head)
		return ;
	while (env_head)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env_head->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
		ft_putstr_fd(env_head->value, STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		env_head = env_head->next;
	}
}

int	add_env(char *argv, int del, t_env_list **env_head)
{
	char		*sep;
	char		*key;
	char		*new_value;
	t_env_list	*key_loc;
	t_env_list	*new_env;

	sep = ft_strchr(argv, del);
	if (!sep)
		return (1);
	key = ft_strndup(argv, sep - argv);
	if (!key)
		return (1);
	key_loc = env_key_location(*env_head, key);
	free(key);
	if (key_loc)
	{
		if (del == '+')
			new_value = ft_strdup(sep + 2);
		else
		{
			new_value = ft_strdup(sep + 1);
			free(key_loc->value);
			key_loc->value = new_value;
		}
	}
	else
	{
		new_env = new_env_list(argv);
		if (!new_env)
			return (1);
		env_add_back(env_head, new_env);
	}
	return (0);
}

int	check_delimeter(char *argv)
{
	char	*sep;

	sep = ft_strchr(argv, '=');
	if (!sep)
		return (NO_DEL);
	if (*(sep - 1) == '+')
		return (ADD_VAL);
	return (ADD_ENV);
}

int	add_value(char *argv, t_env_list *env_head)
{
	char		*sep;
	char		*key;
	char		*join_value;
	t_env_list	*add_loc;

	sep = ft_strchr(argv, '+');
	if (!sep)
		return (1);
	key = ft_strndup(argv, sep - argv);
	if (!key)
		return (1);
	add_loc = env_key_location(env_head, key);
	free(key);
	if (!add_loc)
		add_env(argv, '+', &env_head);
	join_value = ft_strjoin(add_loc->value, sep + 2);
	free(add_loc->value);
	add_loc->value = join_value;
	return (0);
}

int	builtin_export(char *argv[], t_mshell_info *info)
{
	int	i;
	int	delimeter;
	int	ret;

	i = -1;
	if (!argv)
		print_export_env(info->env_head);
	while (argv[++i])
	{
		ret = 0;
		delimeter = check_delimeter(argv[i]);
		if (delimeter == ADD_VAL)
			ret = add_value(argv[i], info->env_head);
		else if (delimeter == ADD_ENV)
			ret = add_env(argv[i], '=', &info->env_head);
		if (ret)
		{
			ft_s_quote_error("export", argv[i], "not a valid identifier");
			return (1);
		}
	}
	return (0);
}