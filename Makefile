# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynenakho <ynenakho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/19 18:23:28 by ynenakho          #+#    #+#              #
#    Updated: 2019/02/27 14:29:08 by ynenakho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
CC = gcc
FLAGS = -Wall -Wextra -Werror -g
SRC = main.c error.c bfs_algo.c hash_table.c
OBJ = $(SRC:.c=.o)

DEPS = lemin.h
LIBS = ./libft/libft.a


all: libftcreate $(NAME)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(FLAGS)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(FLAGS) $(LIBS)

libftcreate:
	@$(MAKE) -C ./libft

clean:
	@$(MAKE) clean -C ./libft
	@/bin/rm -f $(OBJ)

fclean: clean
	@$(MAKE) fclean -C ./libft
	@/bin/rm -f $(NAME)

re: fclean all
