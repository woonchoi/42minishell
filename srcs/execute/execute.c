/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasong <jasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 20:32:05 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/11 18:05:57 by jasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_line(t_mshell_info *info, char *line)
{
	t_expand_token	exp_v;

	init_expand_token_value(&exp_v);
	while (line[exp_v.i])
	{
		if (line[exp_v.i] == '$')
		{
			preprocess_expand_ds(line, &exp_v);
			expand_envvars(line, &exp_v, info->env_head);
		}
		exp_v.i++;
	}
	if (exp_v.i != exp_v.j)
		expand_remain_string(line, &exp_v);
	return (exp_v.str1);
}

void	init_heredoc(t_mshell_info *info, char *str, int *i)
{
	char	*line;
	char	*temp;
	int		len;

	while (1)
	{
		len = ft_strlen(str);
		line = preadline("> ");
		if (ft_strlen(line) > len)
			len = ft_strlen(line);
		if (line != NULL && ft_strncmp(line, str, len))
		{
			temp = line;
			line = expand_line(info, line);
			safety_free(temp);
			ft_putendl_fd(line, info->heredoc[*i].fd[1]);
			safety_free(line);
		}
		else
			break ;
	}
	safety_free(line);
}

void	set_heredoc(t_mshell_info *info, char *str, int *i)
{
	pipe(info->heredoc[*i].fd);
	init_heredoc(info, str, i);
	close(info->heredoc[*i].fd[1]);
	(*i)++;
}

void	preorder_redirection(t_tree *node, t_mshell_info *info, int *i)
{
	if (!node || !node->l_child)
		return ;
	if (node->l_child->type == HEREDOC)
		set_heredoc(info, node->r_child->token, i);
	else
		preorder_redirection(node->l_child, info, i);
		preorder_redirection(node->r_child, info, i);
}

void	run_heredoc(t_mshell_info *info)
{
	t_tree	*cur;
	int		i;
	int		heredoc_i;

	i = -1;
	heredoc_i = 0;
	while (++i < info->cmd_count + 1)
	{
		cur = info->tree[i].root->l_child;
		preorder_redirection(cur, info, &heredoc_i);
	}
}

void	heredoc_process(t_mshell_info *info)
{
	int	h_cnt;

	h_cnt = info->heredoc_count;
	if (h_cnt == 0)
		return ;
	info->heredoc = (t_heredoc *)ft_calloc(sizeof(t_heredoc), h_cnt);
	run_heredoc(info);
}

int	no_fork_cmd(t_tree *node)
{
	char	*cmd;
	int		len;

	if (!node || !node->r_child || !node->r_child->l_child)
		return (TRUE);
	cmd = node->r_child->l_child->token;
	if (cmd);
	{
		len = ft_strlen(cmd);
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
	//printf("!!!!!\n");
	//printf("%s\n", cmd);
	//printf("!!!!\n");
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

int	input_redir(char *pathname)
{
	int	fd;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		return (130);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	output_redir(char *pathname)
{
	int	fd;

	fd = open(pathname, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (130);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	append_redir(char *pathname)
{
	int	fd;

	fd = open(pathname, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		return (130);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	heredoc(t_mshell_info *info)
{
	int	i;

	i = 0;
	while (info->heredoc[i].check)
		i++;
	if (dup2(info->heredoc[i].fd[0], STDIN_FILENO) == -1)
		return (130);
	info->heredoc[i].check = TRUE;
	close(info->heredoc[i].fd[0]);
	return (0);
}

int	execute_redirection(t_mshell_info *info, t_tree *node)
{
	if (node->l_child->type == INPUT_R)
		return (input_redir(node->r_child->token));
	else if (node->l_child->type == OUTPUT_R)
		return (output_redir(node->r_child->token));
	else if (node->l_child->type == APPEND_R)
		return (append_redir(node->r_child->token));
	else if (node->l_child->type == HEREDOC)
		return (heredoc(info));
	return (0);
}

char	**get_path_env_list(t_mshell_info *info)
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

char	*get_cmd_path(t_mshell_info *info, char *token)
{
	char	*temp;
	char	**path_list;

	path_list = get_path_env_list(info);
	if (!path_list)
	{
		info->error = TRUE;
		return (NULL);
	}
}

int		execute_builtin(t_mshell_info *info, int cmd, char **optarg)
{
	//printf("check1 current cmd = %d\n", cmd);
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
	//printf("check2\n");
	return (0);
}

int		execute_cmd(t_mshell_info *info, t_tree *node)
{
	char	*cmd;
	char	**optarg;
	int		builtin_cmd;

	optarg = NULL;
	builtin_cmd = check_builtin(node->l_child->token);
	if (builtin_cmd)
	{
		if (node->r_child)
			optarg = ft_split(node->r_child->token, '\n');
		g_exit_status = execute_builtin(info, builtin_cmd, optarg);
	}
	cmd = get_cmd_path(info, node->l_child->token);
	return (0);
}

void	preorder(t_mshell_info *info, t_tree *node)
{
	//printf("preorder\n");
	if (!node)
		return ;
	if (node->l_child && is_redirection(node->l_child->type))
	{
		g_exit_status = execute_redirection(info, node);
		if (!g_exit_status)
			return ;
	}
	else if (node->l_child && node->l_child->type == CMD)
	{
		if(execute_cmd(info, node))
			return ;
	}
	preorder(info, node->l_child);
	preorder(info, node->r_child);
}

void	preorder_once(t_mshell_info *info, t_tree *node)
{
	int	in;
	int	out;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	preorder(info, node);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
}

void	preorder_general(t_mshell_info *info, t_tree_list *tree)
{
	int	in;
	int	out;
	int	i;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	i = -1;
	while (++i < info->cmd_count + 1)
	{
		if (i < info->cmd_count)
		{
			pipe(tree[i].fd);
			tree[i + 1].prev_fd = dup(tree[i].fd[0]);
			close(tree[i].fd[0]);
		}
	}
}

void	execute(t_mshell_info *info)
{
	//printf("checkexecute\n");
	if (info->error == TRUE)
		return ;
	//printf("checkexecute\n");
	heredoc_process(info);
	if (no_fork_cmd(info->tree[0].root) && info->cmd_count == 0)
		preorder_once(info, info->tree[0].root);
	else
		preorder_general(info, info->tree);
}