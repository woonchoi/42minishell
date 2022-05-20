/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 23:28:50 by woonchoi          #+#    #+#             */
/*   Updated: 2022/05/21 00:01:56 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/struct.h" //fix makefile soon
#include "../includes/minishell.h"

static void	terminate_arg(int argc, char **argv)
{
	free(argv[argc - 1]);
}

//int	main(int argc, char **argv, char **envp)
int main(int argc, char **argv)
{
	terminate_arg(argc, argv);
	set_signal();
	prompt();
	return (0);
}