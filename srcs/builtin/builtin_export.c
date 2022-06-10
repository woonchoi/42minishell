/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:10:41 by jasong            #+#    #+#             */
/*   Updated: 2022/06/10 20:30:49 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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

int	add_env(char *argv, t_env_list **env_head)
{
	char		*sep;
	t_env_list	*new_env;

	sep = ft_strchr(argv, '=');
	if (!sep)
		return (FALSE);
	new_env = new_env_list(argv);
	if (!new_env)
		return (FALSE);
	env_add_back(env_head, new_env);
	return (TRUE);
}

int	builtin_export(char *argv[], t_mshell_info *info)
{
	int	i;

	i = -1;
	if (argv[0] == NULL)
		print_export_env(info->env_head);
	while (argv[++i])
	{
		if (!add_env(argv[i], &info->env_head))
		{
			ft_s_quote_error("export", argv[i], "not a valid identifier");
			return (1);
		}	
	}
	return (0);
}