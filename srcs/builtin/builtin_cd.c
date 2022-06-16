/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:26:19 by jasong            #+#    #+#             */
/*   Updated: 2022/06/16 19:19:13 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_home_path(char *path, char *home)
{
	char	*ret_path;

	ret_path = NULL;
	if (!path)
		ret_path = home;
	else if (!ft_strncmp(path, "~", 1))
	{
		if (!path[1])
			ret_path = home;
		if (path[1] == '/')
		{
			ret_path = ft_strjoin(home, path + 1);
			safety_free((void **)&home);
		}
	}
	if (ret_path)
		return (ret_path);
	return (ft_strdup(path));
}

int	builtin_cd(char **path, t_info *info)
{
	int		ret;
	char	*cd_path;
	char	*home_path;

	home_path = get_value_with_key("HOME", info->env_head);
	if (path[1] && path[2])
	{
		safety_free((void **)&home_path);
		ft_error("cd", NULL, "too many arguments");
		return (1);
	}
	else
		cd_path = expand_home_path(path[1], home_path);
	ret = chdir(cd_path);
	if (ret == -1)
	{
		info->error = TRUE;
		ft_error("cd", cd_path, strerror(2));
		return (1);
	}
	safety_free((void **)&cd_path);
	return (ret);
}
