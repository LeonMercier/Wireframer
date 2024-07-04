/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:41:08 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/04 17:42:37 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	print_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			ft_printf("%i ", map->arr[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	kbd_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int	ft_draw(t_map *map, mlx_image_t *image)
{
	(void) map;
	set_all_pixels(image, 0x000000FF);
//	draw_square(image, 20, 40, 80, 0xFF0000FF);
	//draw_map_simple(map, image);
	t_line line;
	line = (t_line){.xa = 60, .ya = 600, .xb = 150, .yb = 200};
	/*
	line.xa = 60;
	line.ya = 600;
	line.xb = 150;
	line.yb = 200;
	*/
	draw_line(image, line, 0xFF0000FF);
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
	read_file(&map, argv[1]);
	print_map(&map);
	start_graphics(&map);
	// one line becomes one int array
	// => 2D array, formatted as [y][x]
	// struct to store array, width and heigth
}
