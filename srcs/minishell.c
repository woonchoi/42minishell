/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 23:28:50 by woonchoi          #+#    #+#             */
/*   Updated: 2022/05/22 19:36:15 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/minishell.h"

static void	terminate_arg(int argc, char **argv)
{
	if (!argv)
		argc += 1;
}

void	test(t_mshell_info *info)
{
	t_env_list	*env_list;
	int			i;

	env_list = info->env_head;
	while (env_list)
	{
		printf("key : %s\n", env_list->key);
		i = 0;
		while (env_list->value[i])
		{
			printf("value(index %d) : %s\n", i, env_list->value[i]);
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
	prompt();
	return (0);
}