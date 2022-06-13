/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasong <jasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:42:01 by jasong            #+#    #+#             */
/*   Updated: 2022/06/13 21:46:32 by jasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **argv)
{
	int	newline_flag;
	int	i;

	newline_flag = FALSE;
	i = 1;
	if (argv[1] == NULL)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		return (0);
	}
	if (argv[i] && !ft_strncmp(argv[i], "-n", 3))
	{
		newline_flag = TRUE;
		++i;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!newline_flag)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
