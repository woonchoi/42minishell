/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constant.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 23:39:56 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/15 10:36:32 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANT_H
# define CONSTANT_H

# define TRUE 1
# define FALSE 0
# define SEPLIST "<>| "
# define SPACELIST " \t\n\v\f\r"
# define METACHARACTER "<>| \t\n\v\f\r"
# define SYNTAX_ERROR_PRE "bash: syntax error near unexpected token `"

typedef enum e_cmd_type
{
	ROOT = 0,
	STR = 1,
	INPUT_R = 2,
	OUTPUT_R = 3,
	APPEND_R = 4,
	HEREDOC = 5,
	CMD = 6,
	OPTARG = 7,
	BRANCH = 8,
}	t_cmd_type;

typedef enum e_builtin_cmd
{
	CMD_CD = 1,
	CMD_PWD = 2,
	CMD_ENV = 3,
	CMD_ECHO = 4,
	CMD_EXIT = 5,
	CMD_UNSET = 6,
	CMD_EXPORT = 7,
}	t_builtin_cmd;

typedef enum e_token_type
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