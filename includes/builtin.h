/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasong <jasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:08:33 by jasong            #+#    #+#             */
/*   Updated: 2022/06/09 18:05:56 by jasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "minishell.h"
# include <string.h>

int		builtin_cd(char *path, t_mshell_info *info);
int		builtin_echo(char *argv[]);
void	ft_error(char *cmd, char *cmd_arg, char *errmsg);

#endif