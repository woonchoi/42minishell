/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constant.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 23:39:56 by woonchoi          #+#    #+#             */
/*   Updated: 2022/05/27 20:52:03 by woonchoi         ###   ########.fr       */
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
	INPUT_R = 1,
	OUTPUT_R = 2,
	APPEND_R = 3,
	HEREDOC = 4,
	CMD = 5,
	OPTARG = 6,
	BRANCH = 7,
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
	NORMAL = 0,
}	t_token_type;

#endif