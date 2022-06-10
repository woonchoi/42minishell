/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error_singlequote.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasong <jasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:44:19 by jasong            #+#    #+#             */
/*   Updated: 2022/06/09 19:17:21 by jasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_s_quote_error(char *cmd, char *cmd_arg, char *errmsg)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("'", 2);
	if (cmd_arg)
	{
		ft_putstr_fd(cmd_arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd("'", 2);
	ft_putstr_fd(errmsg, 2);
	ft_putstr_fd("\n", 2);
}