# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: woonchoi <woonchoi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/20 23:20:32 by woonchoi          #+#    #+#              #
#    Updated: 2022/05/30 17:50:23 by jasong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAG = -Wall -Wextra -Werror -g -fsanitize=address
LIBFT_DIR = ./lib/libft/
LIBFT = $(LIBFT_DIR)libft.a
INC_DIR = ./includes/
LOCAL_READLINE_DIR = /opt/homebrew/opt/readline
CLUSTER_RL_DIR = $(HOME)/.brew/opt/readline


LIBRARIES= -L$(LIBFT_DIR) -L$(LOCAL_READLINE_DIR)/lib -L$(CLUSTER_RL_DIR)/lib
INCLUDES = -I$(LIBFT_DIR) -I$(INC_DIR) -I$(LOCAL_READLINE_DIR)/include $(CLUSTER_RL_DIR)/include

SRC_DIR = ./srcs/

MAIN_SRCS = signal_handler.c prompt.c minishell.c init_prompt.c
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
