/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:04:23 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/05 15:07:58 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>

typedef struct	s_point
{
	double	screen_x;
	double	screen_y;
	int	depth;
}	t_point;

typedef struct	s_map
{
	t_point **arr;
	int	cols;
	int	rows;
}	t_map;

typedef struct	s_line
{
	unsigned int	xa;
	unsigned int	ya;
	unsigned int	xb;
	unsigned int	yb;
}	t_line;

int	ft_atoi_safe2(const char *str, int *err_atoi);
// read_file.c
int	read_file(t_map *map, char *filename);
// draw_tools.c
void	set_all_pixels(mlx_image_t *image, uint32_t color);
void	draw_line(mlx_image_t *image, t_line line, uint32_t color);

#endif
