/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasong <jasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:57:20 by jasong            #+#    #+#             */
/*   Updated: 2022/06/09 17:16:08 by jasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_env(char *argv[], t_env_list *env_head)
{
	if (!argv[0])
	{
		ft_error("env", argv[0], strerror(1));
		return (127);
	}
	while (env_head)
	{
		ft_putstr_fd(env_head->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		if (env_head->value && env_head->value[0])
			ft_putstr_fd(env_head->value, STDOUT_FILENO);
		env_head = env_head->next;
	}
	return (0);
}