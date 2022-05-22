/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 23:40:14 by woonchoi          #+#    #+#             */
/*   Updated: 2022/05/22 19:18:26 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct	s_env_list
{
	char				*key;
	char				**value;
	struct s_env_list	*next;
}	t_env_list;

typedef struct	s_mshell_info
{
	t_env_list	*env_head;
}	t_mshell_info;

#endif