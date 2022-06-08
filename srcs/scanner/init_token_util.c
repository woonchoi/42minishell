/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:24:49 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/08 19:25:11 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_expand_token_value(t_expand_token *exp_v)
{
	exp_v->str1 = NULL;
	exp_v->str2 = NULL;
	exp_v->i = 0;
	exp_v->j = 0;
	exp_v->qstatus = NO_Q;
}
