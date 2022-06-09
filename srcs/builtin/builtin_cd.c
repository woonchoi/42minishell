/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasong <jasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:26:19 by jasong            #+#    #+#             */
/*   Updated: 2022/06/08 19:40:27 by jasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char *path, t_mshell_info *info)
{
	int	ret;

	// if (!path || !path[0])
	// 	path = home_path(info); // homepath 작성해야함...
	ret = chdir(path);
	if (ret == -1)
	{
		info->error = TRUE;
		ft_error("cd", path, strerror(2));
		return (1);
	}
	return (ret);
}
