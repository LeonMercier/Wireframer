# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 11:56:58 by lemercie          #+#    #+#              #
#    Updated: 2024/07/10 16:18:55 by lemercie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= fdf
#CFLAGS	:= -g -Wextra -Wall -Werror -Wunreachable-code -Ofast
CFLAGS	:= -g -Wextra -Wall -Werror -Wunreachable-code
LIBMLX	:= ./lib/MLX42
LIBFT	:= ./lib/libft

HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCDIR	:= ./src/
SRCS	:= $(SRCDIR)fdf.c $(SRCDIR)ft_atoi_safe2.c $(SRCDIR)read_file.c \
		   $(SRCDIR)draw_tools.c
OBJS	:= ${SRCS:.c=.o}

all: libft libmlx $(NAME)

.libmlx_cloned: 
	git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX)
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	touch .libmlx_cloned

libmlx: .libmlx_cloned

.libft_cloned: 
	git clone git@github.com:LeonMercier/libft_plus.git $(LIBFT)
	make -C $(LIBFT)
	touch .libft_cloned

libft: .libft_cloned

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) 

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(LIBFT)/libft.a $(HEADERS) -o $(NAME)

clean:
	rm .libmlx_cloned
	rm .libft_cloned
	rm -rf $(OBJS)
	rm -rf $(LIBMLX)/build

fclean: clean
	rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
