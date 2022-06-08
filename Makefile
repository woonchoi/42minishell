# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/20 23:20:32 by woonchoi          #+#    #+#              #
#    Updated: 2022/06/08 19:33:05 by woonchoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAG = -g -fsanitize=address
LIBFT_DIR = ./lib/libft/
LIBFT = $(LIBFT_DIR)libft.a
INC_DIR = ./includes/
CLUSTER_RL_DIR = $(HOME)/.brew/opt/readline


LIBRARIES= -L$(LIBFT_DIR) -L$(CLUSTER_RL_DIR)/lib
INCLUDES = -I$(LIBFT_DIR) -I$(INC_DIR) -I$(CLUSTER_RL_DIR)/include

SRC_DIR = ./srcs/

MAIN_SRCS = signal_handler.c prompt.c minishell.c init_prompt.c init_struct.c\
			lexer/tokenizer.c lexer/create_token_list.c lexer/lexer.c lexer/tokenizing_util.c lexer/validate_token_list.c\
			scanner/expand_envvars.c scanner/expand_tokens.c scanner/expand_util.c scanner/get_token_env.c scanner/init_token_util.c scanner/scanner.c\
			util_free/safety_free.c\
			parser/build_parse_tree.c parser/init_parser.c parser/parse_result_util.c parser/parser_add_tree_node.c parser/parser.c\
			util_free/terminate_free.c\


MAIN_SRCDIR = $(addprefix $(SRC_DIR), $(MAIN_SRCS))

SRCS = $(MAIN_SRCDIR)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAG) $(LIBRARIES) $(INCLUDES) $(OBJS) -o $(NAME) -lft -lreadline

%.o: %.c
	@$(CC) $(CFLAG) -c $(INCLUDES) $< -o $@

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR) all

clean:
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS)

fclean:
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@rm -rf $(OBJS)
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re
