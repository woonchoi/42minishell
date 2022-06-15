/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmd_optarg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:17:55 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/15 15:13:04 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_cmd_optarg(t_tree *node)
{
	char	*cmdopt;
	char	*temp;

	cmdopt = ft_strdup(node->l_child->token);
	temp = cmdopt;
	cmdopt = ft_strjoin(cmdopt, "\n");
	safety_free((void **)&temp);
	if (node->r_child)
	{
		temp = cmdopt;
		cmdopt = ft_strjoin(cmdopt, node->r_child->token);
		safety_free((void **)&temp);
	}
	return (cmdopt);
}
