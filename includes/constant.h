/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constant.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 23:39:56 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/06 14:49:22 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANT_H
# define CONSTANT_H

# define TRUE 1
# define FALSE 0
# define SEPLIST "<>| "
# define SPACELIST " \t\n\v\f\r"

typedef enum	e_cmd_type
{
	ROOT = 0,
	NORMAL = 1,
	INPUT_R = 2,
	OUTPUT_R = 3,
	APPEND_R = 4,
	HEREDOC = 5,
	CMD = 6,
	OPTARG = 7,
	BRANCH = 8,
}	t_cmd_type;

typedef enum	e_token_type
{
	DOUBLE_Q = '"',
	SINGLE_Q = '\'',
	NO_Q = -1,
	LEFT_ANGLE = '<',
	RIGHT_ANGLE = '>',
	DOLLAR = '$',
	PIPE = '|',
	BACK_SLASH = '\\',
	GRAVE = '`',
	SP = ' ',
	NL = '\n',
}	t_token_type;

#endif