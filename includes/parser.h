/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:02:11 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/08 16:47:45 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

void	init_tree_with_pipecount(t_mshell_info *info);
void	init_parse_util(t_parse_util *par_v, t_tree *root);

t_tree	*create_node(int type, char *token, t_mshell_info *info);
void	add_cmd_arg(t_tree **parent, char *s, t_mshell_info *info);
void	add_cmd_node(t_tree **parent, char *s, int t, t_mshell_info *info);
void	add_arg_node(t_tree **parent, char *s, int t, t_mshell_info *info);
void	add_red_node(t_tree **parent, char *s, int t, t_mshell_info *info);

void	print_tree_result(t_tree *root);

void	build_tree(t_mshell_info *info);

#endif