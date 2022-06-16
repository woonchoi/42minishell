/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:44:19 by jasong            #+#    #+#             */
/*   Updated: 2022/06/15 23:28:17 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *cmd, char *cmd_arg, char *errmsg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (cmd_arg)
	{
		ft_putstr_fd(cmd_arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(errmsg, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_s_quote_error(char *cmd, char *cmd_arg, char *errmsg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("`", 2);
	if (cmd_arg)
		ft_putstr_fd(cmd_arg, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(errmsg, 2);
	ft_putstr_fd("\n", 2);
}
