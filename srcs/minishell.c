/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 23:28:50 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/01 21:58:55 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "../includes/minishell.h"

static void	terminate_arg(int argc, char **argv)
{
	if (!argv)
		argc += 1;
	argc = (int)argc;
}

void	test(t_mshell_info *info)
{
	t_env_list	*env_list;
	int			i;

	env_list = info->env_head;
	while (env_list)
	{
		printf("key : %s\n", env_list->key);
		printf("value : %s\n", env_list->value);
		i = 0;
		while (env_list->split_value[i])
		{
			printf("value(index %d) : %s\n", i, env_list->split_value[i]);
			i++;
		}
		env_list = env_list->next;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_mshell_info	info;

	terminate_arg(argc, argv);
	set_signal();
	init_mshell_info(&info, envp);
	test(&info);
	prompt(&info);
	return (0);
}
