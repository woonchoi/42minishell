/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:12:53 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/13 13:15:10 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_heredoc(t_info *info)
{
	t_tree	*cur;
	int		i;
	int		heredoc_i;

	i = -1;
	heredoc_i = 0;
	while (++i < info->cmd_count)
}

void	heredoc_process(t_info *info)
{
	int	h_cnt;

	h_cnt = info->heredoc_count;
	if (h_cnt == 0)
		info->heredoc = (t_heredoc *)ft_calloc(sizeof(t_heredoc), h_cnt);
	run_heredoc(info);
}
