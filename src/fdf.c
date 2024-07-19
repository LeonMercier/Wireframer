/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:41:08 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/19 11:16:29 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	kbd_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int	ft_draw(t_map *map, mlx_image_t *image)
{
	set_all_pixels(image, 0x000000FF);
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

// handles both zooming in and zooming out
void	fit_to_image(t_map *map, int image_width, int image_heigth)
{
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

// TODO: match oriontation of test executable?
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
	image_width = 1600;
	image_heigth = 1000;
	if (read_file(&map, argv[1]) == -1)
		return (0);
	ft_printf("initial map\n");
	//print_map(&map);
	ft_printf("\n");
	ft_printf("flatened map\n");
	flatten(&map, 1.1);
	print_map(&map);
	ft_printf("isometric map\n");
	to_isometric(&map);
	//print_map_2d(&map);
	
//	ft_zoom(&map, 20);
	fit_to_image(&map, image_width, image_heigth);
	//print_map_2d(&map);
	shift_top_left(&map);
	//print_map_2d(&map);
	start_graphics(&map, image_width, image_heigth);
}
