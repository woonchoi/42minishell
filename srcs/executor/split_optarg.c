/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_optarg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 22:22:02 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/15 22:42:10 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_optarg(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			cnt++;
		i++;
	}
	return (cnt + 1);
}

char	**split_optarg(char *str)
{
	char	**ret;
	int i;
	int j;
	int	cur;

	i = 0;
	j = 0;
	cur = 0;
	ret = (char **)ft_calloc(count_optarg(str), sizeof(char *) + 1);
	while (str && str[j])
	{
		if (str[j] == '\n')
		{
			ret[cur] = ft_strndup(&str[i], j - i);
			cur++;
			i = j + 1;
		}
		j++;
	}
	ret[cur] = ft_strndup(&str[i], j - i);
	return (ret);
}