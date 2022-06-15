/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:12:53 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/15 21:22:59 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_process(t_info *info)
{
	int	h_cnt;

	h_cnt = info->heredoc_count;
	if (h_cnt == 0)
		return ;
	info->heredoc = (t_heredoc *)ft_calloc(sizeof(t_heredoc), h_cnt + 1);
	run_heredoc(info);
}
