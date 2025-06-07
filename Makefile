# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: JuHyeon <juhyeonl@student.hive.fi>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/16 20:08:16 by JuHyeon           #+#    #+#              #
#    Updated: 2025/05/17 00:00:00 by JuHyeon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = srcs/child.c \
       srcs/execute.c \
       srcs/find_path.c \
       srcs/ft_count_words_quoted.c \
       srcs/main.c \
       srcs/parse_quoted_cmd.c \
       srcs/utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME)

libft/libft.a:
	make -C libft

%.o: %.c include/pipex.h
	$(CC) $(CFLAGS) -I include -c $< -o $@

clean:
	$(RM) $(OBJS)
	make -C libft clean

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
