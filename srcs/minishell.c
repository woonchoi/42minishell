/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasong <jasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 23:28:50 by woonchoi          #+#    #+#             */
/*   Updated: 2022/05/23 14:47:04 by jasong           ###   ########.fr       */
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