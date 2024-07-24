# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 11:56:58 by lemercie          #+#    #+#              #
#    Updated: 2024/07/24 10:11:13 by lemercie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= cc
CFLAGS	:= -Wextra -Wall -Werror
NAME	:= fdf
LIBMLX	:= ./lib/MLX42
LIBFT	:= ./lib/libft

HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCDIR	:= ./src/
SRCS	:= $(addprefix $(SRCDIR),fdf.c read_file.c \
		   draw_tools.c connect_points.c ft_zoom.c shift_top_left.c \
		   to_isometric.c map_tools.c utils.c fit_to_image.c)
OBJS	:= ${SRCS:.c=.o}

all: libft libmlx $(NAME)

.libmlx_cloned: 
	git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX)
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	touch .libmlx_cloned

libmlx: .libmlx_cloned

libft: 
	make -C $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) 

$(NAME): $(OBJS) ./include/fdf.h
	$(CC) $(OBJS) $(LIBS) $(LIBFT)/libft.a $(HEADERS) -o $(NAME)

clean:
	rm -rf $(OBJS)
	make clean -C $(LIBFT)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT)

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft
