/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasong <jasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:42:01 by jasong            #+#    #+#             */
/*   Updated: 2022/06/09 01:39:36 by jasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char *argv[]) //argv에 들어오는 내용은 data로 들어와야함 ex) echo "$HOME" > /Users/jasong
{
	int	newline_flag;
	int	i;

	newline_flag = FALSE;
	i = 0;
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
	if (newline_flag)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}