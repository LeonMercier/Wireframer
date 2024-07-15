/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:41:08 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/15 14:30:48 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <stdio.h> //debugging
void	print_map(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			printf("%i ", map->arr[y][x].depth);
			x++;
		}
		printf("\n");
		y++;
	}
}

void	print_map_2d(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			printf("%.1f,%.1f ", map->arr[y][x].screen_x, map->arr[y][x].screen_y);
			x++;
		}
		printf("\n");
		y++;
	}
}
void	kbd_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void	connect_points(t_map *map, mlx_image_t *image)
{
	int	y;
	int	x;
	t_line	line;

//	(void) image;
	y = 0;
	while (y < map->rows - 1)
	{
		x = 0;
		while (x < map->cols - 1)
		{
			line.xa = lround(map->arr[y][x].screen_x);
			line.ya = lround(map->arr[y][x].screen_y);
			line.xb = lround(map->arr[y][x + 1].screen_x);
			line.yb = lround(map->arr[y][x + 1].screen_y);
//			printf("%f, %f, %f, %f\n", line.xa, line.ya, line.xb, line.yb);
			draw_line(image, line, 0xFF0000FF);
			line.xa = lround(map->arr[y][x].screen_x);
			line.ya = lround(map->arr[y][x].screen_y);
			line.xb = lround(map->arr[y + 1][x].screen_x);
			line.yb = lround(map->arr[y + 1][x].screen_y);
//			printf("%f, %f, %f, %f\n", line.xa, line.ya, line.xb, line.yb);
			draw_line(image, line, 0xFF0000FF);
			x++;
		}
		y++;
	}
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

void	to_isometric(t_map *map)
{
	int	y;
	int	x;
	double	angle;

	y = 0;
	angle = 0.52; // 30 deg in rads
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			map->arr[y][x].screen_x =
				(x * cos(angle)) +
				 (y * cos(angle + 2.09)) + //120 deg in rads
				 (map->arr[y][x].depth * cos(angle - 2.09));
			map->arr[y][x].screen_y =
				(x * sin(angle)) +
				 (y * sin(angle + 2.09)) + //120 deg in rads
				 (map->arr[y][x].depth * sin(angle - 2.09));
			x++;
		}
		y++;
	}
}
void	ft_zoom(t_map *map, double zoomfactor)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			map->arr[y][x].screen_x *= zoomfactor;
			map->arr[y][x].screen_y *= zoomfactor;
			x++;
		}
		y++;
	}
}

void	get_min_coords(t_map *map, t_point *min)
{
	int	y;
	int	x;

	min->screen_x = map->arr[0][0].screen_x;
	min->screen_y = map->arr[0][0].screen_y;
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			if (map->arr[y][x].screen_x < min->screen_x)
				min->screen_x = map->arr[y][x].screen_x;
			if (map->arr[y][x].screen_y < min->screen_y)
				min->screen_y = map->arr[y][x].screen_y;
			x++;
		}
		y++;
	}	
}

void	shift_coords(t_map *map, double yshift, double xshift)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			map->arr[y][x].screen_x += xshift;
			map->arr[y][x].screen_y += yshift;
			x++;
		}
		y++;
	}
}

void	shift_top_left(t_map *map)
{
	t_point	min;

	get_min_coords(map, &min);
	shift_coords(map, - min.screen_y, - min.screen_x);
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
