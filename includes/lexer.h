/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:28:44 by woonchoi          #+#    #+#             */
/*   Updated: 2022/06/12 19:11:29 by woonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "struct.h"

void	validate_syntax(t_info *info);

t_token	*create_token(int type, char *str);
t_token	*token_add_back(t_token *token, int type, char *str);
void	string_add_back(t_info *info);
void	redirection_add_back(t_info *info);

int		get_qstatus(char c, int qstatus);
int		check_quote(t_info *info);
int		is_in_charset(char c, const char *charset);
int		is_only_space(char *str);
int		is_redirection(int tokentype);

void	tokenizer(t_info *info);

void	lexer(t_info *info);

#endif