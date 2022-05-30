/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 23:40:14 by woonchoi          #+#    #+#             */
/*   Updated: 2022/05/28 00:03:49 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct	s_env_list
{
	char				*key;
	char				**value;
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
	t_tree		*root;
	struct s_tree_list	*next;
}	t_tree_list;

typedef struct	s_token
{
	int		tokentype;
	char	*token;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct	s_parse_info
{
	int			cmd_count;
	t_tree_list	*head;
}	t_parse_info;

typedef struct	s_token_info
{
	int			qstatus;
	t_token		*tokenlist;
}	t_token_info;

typedef struct	s_mshell_info
{
	t_token_info	tinfo;
	t_parse_info	pinfo;
	t_tree_list		*head;
	char			*input;
	int				error;
	int				index;
}	t_mshell_info;

#endif