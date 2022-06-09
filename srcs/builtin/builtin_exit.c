/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasong <jasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:56:23 by jasong            #+#    #+#             */
/*   Updated: 2022/06/09 18:25:23 by jasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	flow(long long num, long long sign)
{
	if (sign > 0)
	{
		if (num * sign < 0)
			return (TRUE);
	}
	else
	{
		if (num * sign > 0)
			return (TRUE);
	}
	return (FALSE);
}

static long long exit_num(char *num)
{
	long long	i;
	long long	neg_sign;
	long long	ret;

	i = 0;
	neg_sign = 1;
	ret = 0;
	if (num[i] == '+' || num[i] == '-')
	{
		if (num[i] == '-')
			neg_sign = -1;
		i++;
	}
	while (num[i] && num[i] >= '0' && num[i] <= '9')
	{
		ret = ret * 10 + num[i++] - '0';
		if (flow(ret, neg_sign))
			return (-1);
	}
	if (num[i])
		return (-1);
	return ((unsigned char)(ret * neg_sign));
}

int	builtin_exit(char *argv[], int pipe_flag) // pipe로 넘어오면 pipe flag = 0
{
	if (!argv[0])
	{
		if (pipe_flag != TRUE)
			ft_putendl_fd("exit", 1);
		exit(0);
	}
	if (exit_num(argv[0]) < 0)
	{
		ft_error("exit", argv[0], "numeric argument required");
		exit(255);
	}
	if (argv[1] != NULL)
	{
		ft_error("exit", NULL, "too many arguments");
		exit(1);
	}
	ft_putstr_fd("exit", 1);
	exit(exit_num(argv[0]));
}