/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:39:20 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/14 12:34:19 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_fork_cmd(t_tree *node)
{
	char	*cmd;

	if (!node || !node->r_child || !node->r_child->l_child)
		return (TRUE);
	cmd = node->r_child->l_child->token;
	if (cmd)
	{
		if (!ft_strncmp(cmd, "cd", 3)
			|| !ft_strncmp(cmd, "env", 4)
			|| !ft_strncmp(cmd, "exit", 5)
			|| !ft_strncmp(cmd, "unset", 6)
			|| !ft_strncmp(cmd, "export", 7))
			return (TRUE);
	}
	return (FALSE);
}

int	check_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 3))
		return (CMD_CD);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (CMD_PWD);
	if (!ft_strncmp(cmd, "env", 4))
		return (CMD_ENV);
	if (!ft_strncmp(cmd, "echo", 5))
		return (CMD_ECHO);
	if (!ft_strncmp(cmd, "exit", 5))
		return (CMD_EXIT);
	if (!ft_strncmp(cmd, "unset", 6))
		return (CMD_UNSET);
	if (!ft_strncmp(cmd, "export", 7))
		return (CMD_EXPORT);
	return (FALSE);
}
