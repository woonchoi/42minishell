/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 22:08:31 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/01 22:03:08 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/minishell.h"

static void	parse_list_add_back(t_env_list **env_list, t_env_list *temp)
{
	t_env_list	*cur;

	if (!*env_list)
		*env_list = temp;
	else
	{
		cur = *env_list;
		while (cur->next)
			cur = cur->next;
		cur->next = temp;
	}
}

static void	parse_env_list(t_env_list **env_list, char **envp)
{
	int			i;
	char		*env_temp;
	t_env_list	*temp;

	i = 0;
	while (envp[i])
	{
		temp = (t_env_list *)malloc(sizeof(t_env_list));
		if (!temp)
			return ; // need to add terminate minishell
		temp->key = ft_strndup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
		env_temp = ft_strchr(envp[i], '=');
		if (env_temp)
			env_temp++;
		temp->value = ft_strdup(env_temp);
		temp->split_value = ft_split(ft_strchr(envp[i], '=') + 1, ':');
		temp->next = 0;
		parse_list_add_back(env_list, temp);
		i++;
	}
}

static t_env_list	*init_env(char **envp)
{
	t_env_list	*env_list;

	env_list = 0;
	parse_env_list(&env_list, envp);
	return (env_list);
}

void	init_mshell_info(t_mshell_info *info, char **envp)
{
	info->cmd_count = 0;
	info->env_head = init_env(envp);
	info->head = 0;
}
