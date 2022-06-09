/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 20:32:05 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/09 16:02:11 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_line(t_mshell_info *info, char *line)
{
	t_expand_token	exp_v;

	init_expand_token_value(&exp_v);
	while (line[exp_v.i])
	{
		if (line[exp_v.i] == '$')
		{
			preprocess_expand_ds(line, &exp_v);
			expand_envvars(line, &exp_v, info->env_head);
		}
		exp_v.i++;
	}
	if (exp_v.i != exp_v.j)
		expand_remain_string(line, &exp_v);
	return (exp_v.str1);
}

void	init_heredoc(t_mshell_info *info, char *str, int *i)
{
	char	*line;
	char	*temp;

	while (1)
	{
		line = preadline("> ");
		if (line != NULL && ft_strncmp(line, str, ft_strlen(str)))
		{
			temp = line;
			line = expand_line(info, line);
			safety_free(temp);
			ft_putendl_fd(line, info->heredoc[*i].fd[1]);
			safety_free(line);
		}
		else
			break ;
	}
	safety_free(line);
}

void	set_heredoc(t_mshell_info *info, char *str, int *i)
{
	pipe(info->heredoc[*i].fd);
	init_heredoc(info, str, i);
	close(info->heredoc[*i].fd[1]);
	(*i)++;
}

void	preorder_redirection(t_tree *node, t_mshell_info *info, int *i)
{
	if (!node || !node->l_child)
		return ;
	if (node->l_child->type == HEREDOC)
		set_heredoc(info, node->r_child->token, i);
	else
		preorder_redirection(node->l_child, info, i);
		preorder_redirection(node->r_child, info, i);
}

void	run_heredoc(t_mshell_info *info)
{
	t_tree	*cur;
	int		i;
	int		heredoc_i;

	i = -1;
	heredoc_i = 0;
	while (++i < info->cmd_count + 1)
	{
		cur = info->tree[i].root->l_child;
		preorder_redirection(cur, info, &heredoc_i);
	}
}

void	heredoc_process(t_mshell_info *info)
{
	int	h_cnt;

	h_cnt = info->heredoc_count;
	if (h_cnt == 0)
		return ;
	info->heredoc = (t_heredoc *)ft_calloc(sizeof(t_heredoc), h_cnt);
	run_heredoc(info);
	safety_free(info->heredoc);
}

void	execute(t_mshell_info *info)
{
	if (info->error == TRUE)
		return ;
	heredoc_process(info);
}