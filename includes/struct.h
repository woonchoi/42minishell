/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 23:40:14 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/06 19:29:26 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct	s_env_list
{
	char				*key;
	char				*value;
	char				**split_value;
	struct s_env_list	*next;
}	t_env_list;

typedef struct	s_tree
{
	int				type;
	char			*token;
	struct s_tree	*l_child;
	struct s_tree	*r_child;
}	t_tree;

typedef struct	s_tree_list
{
	int			fd[2];
	pid_t		pid;
	t_tree		*root;
}	t_tree_list;

typedef struct	s_token
{
	int		tokentype;
	char	*token;
	char	*token_origin;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct	s_token_info
{
	int			qstatus;
	t_token		*tokenlist;
}	t_token_info;

typedef struct	s_expand_token
{
	char	*str1;
	char	*str2;
	int		i;
	int		j;
	int		qstatus;
}	t_expand_token;

typedef struct	s_parse_util
{
	t_tree	*red_cur;
	t_tree	*cmd_cur;
	char	*temp;
	int		cmd_status;
	int		red_status;
	int		heredoc_status;
	int		heredoc_count;
}	t_parse_util;

typedef struct	s_mshell_info
{
	t_token_info	tinfo;
	t_tree_list		*tree;
	t_env_list		*env_head;
	int				cmd_count;
	char			*input;
	int				error;
	int				index;
	int				heredoc_count;
}	t_mshell_info;

#endif