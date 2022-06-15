/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:27:17 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/15 10:34:36 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit_status(t_info *info)
{
	int	status;
	int	i;

	i = -1;
	while (++i < info->cmd_count)
	{
		if (waitpid(info->tree[i].pid, &status, 0) == -1)
			exit(1);
	}
	return (1);
}
