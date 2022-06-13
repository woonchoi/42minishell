/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:26:19 by jasong            #+#    #+#             */
/*   Updated: 2022/06/12 19:11:29 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char **path, t_info *info)
{
	int		ret;
	char	*cd_path;

	if (!path)
		cd_path = get_value_with_key("HOME", info->env_head);
	else if (path[0] && path[1])
	{
		ft_error("cd", NULL, "too many arguments");
		return (1);
	}
	else
		cd_path = path[0];
	ret = chdir(cd_path);
	if (ret == -1)
	{
		info->error = TRUE;
		ft_error("cd", cd_path, strerror(2));
		return (1);
	}
	return (ret);
}
