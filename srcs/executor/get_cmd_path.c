/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:26:18 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/14 12:36:05 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path_env_list(t_info *info)
{
	t_env_list	*cur;

	cur = info->env_head;
	while (cur)
	{
		if (!ft_strncmp(cur->key, "PATH", 5))
			break ;
		cur = cur->next;
	}
	if (cur)
		return (cur->split_value);
	return (NULL);
}

char	*strjoin_free(char *a, char *b)
{
	char	*temp;

	temp = ft_strjoin(a, b);
	safety_free(a);
	return (temp);
}

char	*match_cmd_path(char *token, char **path)
{
	struct stat	buf;
	char		*temp;
	int			i;

	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		temp = strjoin_free(temp, token);
		if (!lstat(temp, &buf))
			return (temp);
		safety_free(temp);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(t_info *info, char *token)
{
	char	*temp;
	char	**path_list;

	temp = NULL;
	path_list = get_path_env_list(info);
	if (!path_list)
	{
		info->error = TRUE;
		return (temp);
	}
	else
		temp = match_cmd_path(token, path_list);
	return (temp);
}
