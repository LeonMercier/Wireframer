/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:04:23 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/23 11:40:24 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>

typedef struct s_point
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

typedef struct s_map
{
	t_point	**arr;
	int		cols;
	int		rows;
}	t_map;

typedef struct s_line
{
	int	xa;
	int	ya;
	int	xb;
	int	yb;
	int	dx;
	int	dy;
	int	inc_x;
	int	inc_y;
	int	color_a;
	int	color_b;
}	t_line;

// read_file.c
int		read_file(t_map *map, int fd);
// draw_tools.c
void	set_all_pixels(mlx_image_t *image, uint32_t color);
void	draw_line(mlx_image_t *image, t_line line);
// fit_to_image.c
void	fit_to_image(t_map *map, int image_width, int image_heigth);
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
void	flatten(t_map *map, double flattenfactor);
int		map_add_row(t_map *map);
// utils.c
void	free_map(t_map *map);
void	free_strv(char **strv);
void	fdf_cleanup(t_map *map);
void	fdf_cleanup_exit(t_map *map);
int		hexchar_to_int(char c);
#endif
