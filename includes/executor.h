/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:47:36 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/13 20:58:10 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

int		no_fork_cmd(t_tree *node);
int		check_builtin(char *cmd);

int		input_redir(char *pathname);
int		output_redir(char *pathname);
int		append_redir(char *pathname);
int		heredoc(t_info *info);
int		execute_redirection(t_info *info, t_tree *node);

int		execute_builtin(t_info *info, int cmd, char **optarg);

int		print_red_error(char *path);

char	**get_path_env_list(t_info *info);
char	*strjoin_free(char *a, char *b);
char	*match_cmd_path(t_info *info, char *token, char **path);
char	*get_cmd_path(t_info *info, char *token);
char	*join_cmd_optarg(t_tree *node);

int		check_exit_status(t_info *info);
void	fork_cmd(t_info *info, int i, int in, int out);

int		execute_cmd(t_info *info, t_tree *node);

void	preorder(t_info *info, t_tree *node);
void	preorder_once(t_info *info, t_tree *node, int in, int out);
void	preorder_general(t_info *info, int *in, int *out);

char	*expand_line(t_info *info, char *line);
void	init_heredoc(t_info *info, char *str, int *i);
void	set_heredoc(t_info *info, char *str, int *i);
void	preorder_heredoc(t_info *info, t_tree *node, int *i);
void	run_heredoc(t_info *info);
void	heredoc_process(t_info *info);

void	executor(t_info *info);

#endif