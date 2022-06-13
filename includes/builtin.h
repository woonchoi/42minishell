/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:08:33 by jasong            #+#    #+#             */
/*   Updated: 2022/06/12 19:11:29 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "minishell.h"
# include <string.h>

int			builtin_cd(char **path, t_info *info);
int			builtin_echo(char **argv);
int			builtin_env(char **argv, t_env_list *env_head);
int			builtin_exit(char **argv, int pipe_flag);
int			builtin_export(char **argv, t_info *info);
int			builtin_pwd(void);
int			builtin_unset(char **argv, t_env_list *env_head);

t_env_list	*env_key_location(t_env_list *env_head, char *key);
void		ft_error(char *cmd, char *cmd_arg, char *errmsg);
void		ft_s_quote_error(char *cmd, char *cmd_arg, char *errmsg);
int			check_avaliable_key(char *key);
void 		free_split_value(char **s_val);

#endif