/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:41:08 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/16 19:08:19 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <stdio.h> //debugging

void	kbd_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int	ft_draw(t_map *map, mlx_image_t *image)
{
//	(void) map;
	set_all_pixels(image, 0x000000FF);
//	t_line line;
//	line = (t_line){.xa = 20, .ya = 30, .xb = 150, .yb = 200};
//	draw_line(image, line, 0xFF0000FF);
	connect_points(map, image);
	return (0);
}

int	start_graphics(t_map *map, int image_width, int image_heigth)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(image_width, image_heigth, "FdF", true);
	if (!mlx)
	{
		ft_printf("Error: failed mlx_init()\n");
		return (-1);
	}
	image = mlx_new_image(mlx, image_width, image_heigth);
	if (!image)
	{
		mlx_close_window(mlx);
		ft_printf("Error: failed mlx_new_image()\n");
		return (-1);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) < 0)
	{
		mlx_close_window(mlx);
		ft_printf("Error: failed mlx_image_to_window()\n");
		return (-1);
	}
	ft_draw(map, image);
	mlx_loop_hook(mlx, kbd_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	(void) map;
	return (0);
}

// TODO: how about a function that iterates over the whole map and applies a
// function passed to it to every t_point?
void	flatten(t_map *map, double flattenfactor)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			map->arr[y][x].depth /= flattenfactor;
			x++;
		}
		y++;
	}
}

// handle both zooming in and zooming out
void	fit_to_image(t_map *map, int image_width, int image_heigth)
{
	// diff between min and max
	double	dy;
	double	dx;
	t_point	min;
	t_point	max;
	double	zoomfactor_y;
	double	zoomfactor_x;

	get_min_coords(map, &min);
	get_max_coords(map, &max);
	dy = fabs(max.screen_y - min.screen_y);
	dx = fabs(max.screen_x - min.screen_x);
	zoomfactor_y = dy / image_heigth;
	zoomfactor_x = dx / image_width;
	ft_zoom(map, fmin(1 / zoomfactor_y, 1 / zoomfactor_x));
}
// store a list of points
// each point has 3D coords
// and 2D coords
// calculate 2D coords from  3D coords
// then we can still see which points to connect based on the 3D coords
// TODO: take advantage of image size being stored in image var
int	main(int argc, char **argv)
{
	int	image_width;
	int	image_heigth;
	t_map	map;

	if (argc == 1)
	{
		ft_printf("Error: Filename missing\n");
		return (1);
	}
	if (argc > 2)
	{
		ft_printf("Error: Too many arguments\n");
		return (1);
	}
	map.arr = 0;
	map.rows = 0;
	map.cols = 0;
	image_width = 1500;
	image_heigth = 800;
	read_file(&map, argv[1]);
	printf("initial map\n");
	print_map(&map);
	printf("\n");
	printf("flatened map\n");
	flatten(&map, 5);
	print_map(&map);
	printf("isometric map\n");
	to_isometric(&map);
	print_map_2d(&map);
	
//	ft_zoom(&map, 20);
	fit_to_image(&map, image_width, image_heigth);
	print_map_2d(&map);
	shift_top_left(&map);
	print_map_2d(&map);
	start_graphics(&map, image_width, image_heigth);
	// one line becomes one int array
	// => 2D array, formatted as [y][x]
	// struct to store array, width and heigth
}
