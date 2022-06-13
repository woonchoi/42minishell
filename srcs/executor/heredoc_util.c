/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:27:30 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/13 16:33:13 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_line(t_info *info, char *line)
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

void	init_heredoc(t_info *info, char *str, int *i)
{
	char	*line;
	char	*temp;
	int		len;

	len = ft_strlen(str) + 1;
	while (TRUE)
	{
		line = preadline("> ");
		if (line != NULL && ft_strncmp(line, str, len))
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

void	set_heredoc(t_info *info, char *str, int *i)
{
	pipe(info->heredoc[*i].fd);
	init_heredoc(info, str, i);
	close(info->heredoc[*i].fd[1]);
	(*i)++;
}

void	preorder_heredoc(t_info *info, t_tree *node, int *i)
{
	if (!node && !node->l_child)
		return ;
	if (node->l_child->type == HEREDOC && !node->r_child)
	{
		ft_putstr_fd(SYNTAX_ERROR_PRE, STDOUT_FILENO);
		ft_putstr_fd("newline'\n", STDOUT_FILENO);
		info->error = TRUE;
		g_exit_status = 258;
		return ;
	}
	else if (node->l_child->type == HEREDOC && node->r_child)
		set_heredoc(info, node->r_child->token, i);
	preorder_heredoc(node->l_child, info, i);
	preorder_heredoc(node->r_child, info, i);
}

void	run_heredoc(t_info *info)
{
	t_tree	*cur;
	int		i;
	int		heredoc_i;

	i = -1;
	heredoc_i = 0;
	while (++i < info->cmd_count && !info->error)
	{
		cur = info->tree[i].root->l_child;
		preorder_heredoc(info, cur, &heredoc_i);
	}
}
