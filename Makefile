# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 11:56:58 by lemercie          #+#    #+#              #
#    Updated: 2024/07/04 17:34:31 by lemercie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= fdf
CFLAGS	:= -g -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= ./lib/MLX42
LIBFT	:= ./lib/libft

HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCDIR	:= ./src/
SRCS	:= $(SRCDIR)fdf.c $(SRCDIR)ft_atoi_safe2.c $(SRCDIR)read_file.c \
		   $(SRCDIR)draw_tools.c
OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) 

$(NAME): $(OBJS)
	make -C ./lib/libft
	$(CC) $(OBJS) $(LIBS) $(LIBFT)/libft.a $(HEADERS) -o $(NAME)

clean:
	rm -rf $(OBJS)
	rm -rf $(LIBMLX)/build

fclean: clean
	rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
