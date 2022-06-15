/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:08:59 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/15 23:44:06 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_info *info, int cmd, char **optarg)
{
	if (cmd == CMD_CD)
		return (builtin_cd(optarg, info));
	if (cmd == CMD_PWD)
		return (builtin_pwd());
	if (cmd == CMD_ENV)
		return (builtin_env(optarg, info->env_head));
	if (cmd == CMD_ECHO)
		return (builtin_echo(optarg));
	if (cmd == CMD_EXIT)
		return (builtin_exit(optarg, !info->cmd_count));
	if (cmd == CMD_UNSET)
		return (builtin_unset(optarg, info->env_head));
	if (cmd == CMD_EXPORT)
		return (builtin_export(optarg, info));
	return (0);
}

int	print_execute_error(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("command not found\n", STDERR_FILENO);
	return (127);
}

int	execute_cmd(t_info *info, t_tree *node)
{
	char	*cmdopt;
	char	*cmdpath;
	char	**optarg;
	int		builtin_cmd;

	cmdopt = join_cmd_optarg(node);
	optarg = split_optarg(cmdopt);
	cmdpath = get_cmd_path(info, optarg[0]);
	builtin_cmd = check_builtin(node->l_child->token);
	if (builtin_cmd)
		g_exit_status = execute_builtin(info, builtin_cmd, optarg);
	else if (cmdpath)
		execve(cmdpath, optarg, info->envp);
	else
	{
		execve(optarg[0], optarg, info->envp);
		g_exit_status = print_execute_error(optarg[0]);
	}
	safety_free((void **)&cmdopt);
	safety_free((void **)&cmdpath);
	safety_free_doublearray((void ***)&optarg);
	return (0);
}
