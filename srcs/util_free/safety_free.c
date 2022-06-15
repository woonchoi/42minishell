/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safety_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:48:43 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/15 15:10:29 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safety_free(void **data)
{
	if (data && *data)
	{
		free(*data);
		*data = NULL;
	}
}

void	safety_free_doublearray(void ***data)
{
	int	i;

	i = 0;
	while (*data[i])
	{
		safety_free(data[i]);
		i++;
	}
	safety_free(*data);
}
