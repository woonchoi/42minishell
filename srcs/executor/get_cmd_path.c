/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:26:18 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/13 17:26:39 by woonchoi         ###   ########.fr       */
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

char	*match_cmd_path(t_info *info, char *token, char **path)
{
	DIR				*cur_dir;
	struct dirent	*cur_dir_info;
	char			*temp;
	int				i;

	i = -1;
	while (path[++i])
	{
		cur_dir = opendir(path[i]);
		cur_dir_info = readdir(cur_dir);
		while (cur_dir_info != NULL)
		{
			if (!ft_strncmp(token, cur_dir_info->d_name, ft_strlen(token) + 1))
			{
				temp = ft_strjoin(path[i], "/");
				temp = strjoin_free(temp, token);
				closedir(cur_dir);
				return (temp);
			}
			cur_dir_info = readdir(cur_dir);
		}
		closedir(cur_dir);
	}
	return (NULL);
}

char	*get_cmd_path(t_info *info, char *token)
{
	char	*temp;
	char	**path_list;
	int		i;

	path_list = get_path_env_list(info);
	if (!path_list)
	{
		info->error = TRUE;
		return (NULL);
	}
	else
		temp = match_cmd_path(info, token, path_list);
	if (temp != NULL)
		return (temp);
	else
		return (token);
}
