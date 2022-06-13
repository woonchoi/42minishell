/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:08:59 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/13 20:25:55 by woonchoi         ###   ########.fr       */
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

int	execute_cmd(t_info *info, t_tree *node)
{
	char	*cmdopt;
	char	*cmdpath;
	char	**optarg;
	int		builtin_cmd;

	cmdopt = join_cmd_optarg(node);
	optarg = ft_split(cmdopt, '\n');
	printf("cmdopt == %s && optarg[0] == %s && optarg[1] == %s\n", cmdopt, optarg[0], optarg[1]);
	cmdpath = get_cmd_path(info, optarg[0]);
	builtin_cmd = check_builtin(node->l_child->token);
	printf("cmdopt == %s && cmdpath == %s\n", cmdopt, cmdpath);
	if (builtin_cmd)
		g_exit_status = execute_builtin(info, builtin_cmd, optarg);
	else if (cmdpath)
		execve(cmdpath, optarg, info->envp);
	else
	{
		execve(optarg[0], optarg, info->envp);
		g_exit_status = 0;
		exit(0);
	}
	safety_free(cmdopt);
	safety_free(cmdpath);
	safety_free_doublearray(optarg);
}
