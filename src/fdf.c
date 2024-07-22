/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:41:08 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/22 16:17:19 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	kbd_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

// TODO use return values of call cleanup?
static int	start_graphics(t_map *map, int image_width, int image_heigth)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(image_width, image_heigth, "FdF", true);
	if (!mlx)
		return (-1);
	image = mlx_new_image(mlx, image_width, image_heigth);
	if (!image)
	{
		mlx_close_window(mlx);
		return (-1);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) < 0)
	{
		mlx_close_window(mlx);
		return (-1);
	}
	set_all_pixels(image, 0x000000FF);
	connect_points(map, image);
	mlx_loop_hook(mlx, kbd_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}

static void	draw_map(t_map *map)
{
	int		image_width;
	int		image_heigth;
	int		margin_px;

	image_width = 1600;
	image_heigth = 1000;
	margin_px = 15;
	flatten(map, 1);
	to_isometric(map);
	fit_to_image(map, image_width - (margin_px * 2), image_heigth
		- (margin_px * 2));
	shift_top_left(map, margin_px, margin_px);
	start_graphics(map, image_width, image_heigth);
}

static int	open_file(t_map *map, char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: Could not open file\n");
		return (-1);
	}
	if (read_file(map, fd) == -1)
	{
		ft_printf("Error: failed to read file\n");
		close(fd);
		free_map(map);
		return (-1);
	}
	return (0);
}

// TODO: match oriontation of test executable?
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
	if (open_file(&map, argv[1]) == -1)
		return (1);
	draw_map(&map);
	return (0);
}
