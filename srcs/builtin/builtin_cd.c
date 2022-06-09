/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasong <jasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:26:19 by jasong            #+#    #+#             */
/*   Updated: 2022/06/09 21:51:25 by jasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char *path, t_mshell_info *info)
{
	int	ret;

	if (!path)
		path = get_value_with_key("HOME", info->env_head);
	ret = chdir(path);
	if (ret == -1)
	{
		info->error = TRUE;
		ft_error("cd", path, strerror(2));
		return (1);
	}
	return (ret);
}
