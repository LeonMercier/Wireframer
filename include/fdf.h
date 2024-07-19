/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:04:23 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/19 13:59:24 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>

typedef struct	s_point
{
	double			screen_x;
	double			screen_y;
	double			depth;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	unsigned char	alpha;
	int				color;
}	t_point;

typedef struct	s_map
{
	t_point **arr;
	int	cols;
	int	rows;
}	t_map;

typedef struct	s_line
{
	int	xa;
	int	ya;
	int	xb;
	int	yb;
}	t_line;

int	ft_atoi_safe2(const char *str, int *err_atoi);
// read_file.c
int	read_file(t_map *map, char *filename);
// draw_tools.c
void	set_all_pixels(mlx_image_t *image, uint32_t color);
void	draw_line(mlx_image_t *image, t_line line, uint32_t color_a,
		uint32_t color_b);
// connect_points.c
void	connect_points(t_map *map, mlx_image_t *image);
// to_isometric.c
void	to_isometric(t_map *map);
// shift_top_left.c
void	shift_top_left(t_map *map, int ymargin, int xmargin);
// ft_zoom.c
void	ft_zoom(t_map *map, double zoomfactor);
// map_tools.c
void	get_min_coords(t_map *map, t_point *min);
void	get_max_coords(t_map *map, t_point *max);
// utils.c
void	fdf_cleanup(t_map *map, char *line);
void	fdf_cleanup_exit(t_map *map, char *line);
// debug.c
void	print_map(t_map *map);
void	print_map_2d(t_map *map);

#endif
