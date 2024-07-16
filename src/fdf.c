/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:41:08 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/16 11:13:57 by lemercie         ###   ########.fr       */
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
//	(void) map;
	set_all_pixels(image, 0x000000FF);
//	t_line line;
//	line = (t_line){.xa = 20, .ya = 30, .xb = 150, .yb = 200};
//	draw_line(image, line, 0xFF0000FF);
	connect_points(map, image);
	return (0);
}

int	start_graphics(t_map *map)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(800, 600, "FdF", true);
	if (!mlx)
	{
		ft_printf("Error: failed mlx_init()\n");
		return (-1);
	}
	image = mlx_new_image(mlx, 800, 600);
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

// store a list of points
// each point has 3D coords
// and 2D coords
// calculate 2D coords from  3D coords
// then we can still see which points to connect based on the 3D coords
int	main(int argc, char **argv)
{
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
	read_file(&map, argv[1]);
	print_map(&map);
	flatten(&map, 8);
	print_map(&map);
	to_isometric(&map);
	print_map_2d(&map);
	ft_zoom(&map, 20);
	print_map_2d(&map);
	shift_top_left(&map);
	print_map_2d(&map);
	start_graphics(&map);
	// one line becomes one int array
	// => 2D array, formatted as [y][x]
	// struct to store array, width and heigth
}
