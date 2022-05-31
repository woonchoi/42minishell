/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 23:46:28 by woonchoi          #+#    #+#             */
/*   Updated: 2022/05/31 20:32:28 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "libft.h"
# include "struct.h"
# include "constant.h"
# include "lexer.h"

int		g_exit_status;

void	signal_handler(int signum);
void	set_signal();

char	*preadline(char *shellname);
void	prompt(t_mshell_info *info);

void	init_mshell_info(t_mshell_info *info, char **envp);

void	lexer(t_mshell_info *info);

/* LEXER */

#endif