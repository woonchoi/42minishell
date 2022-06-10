/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasong <jasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:08:33 by jasong            #+#    #+#             */
/*   Updated: 2022/06/10 15:59:07 by jasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "minishell.h"
# include <string.h>

int		builtin_cd(char *path, t_mshell_info *info);
int		builtin_echo(char *argv[]);
int		builtin_env(char *argv[], t_env_list *env_head);
int		builtin_exit(char *argv[], int pipe_flag);
int		builtin_export(char *argv[], t_mshell_info *info);
int		builtin_pwd(void);
int		builtin_unset(t_env_list *env_head, char *argv[]);

void	ft_error(char *cmd, char *cmd_arg, char *errmsg);
void	ft_s_quote_error(char *cmd, char *cmd_arg, char *errmsg);
int		check_avaliable_key(char *key);

#endif