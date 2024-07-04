/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:41:08 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/04 15:40:50 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../lib/MLX42/include/MLX42/MLX42.h"

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

void	draw_square(mlx_image_t *image, unsigned int width, unsigned int x,
		unsigned int y, uint32_t color)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < width && i + x < image->width)
	{
		j = 0;
		while (j < width && j + y < image->width)
		{
			mlx_put_pixel(image, i + x, j + y, color);
			j++;
		}
		i++;
	}
}

void	set_all_pixels(mlx_image_t *image, uint32_t color)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < image->width)
	{
		j = 0;
		while (j < image->height)
		{
			mlx_put_pixel(image, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_map_simple(t_map *map, mlx_image_t *image)
{
	unsigned int	x;
	unsigned int	y;
	int				col;
	int				row;

	x = 0;
	col = 0;
	while (col < map->cols)
	{
		y = 0;
		row = 0;
		while (row < map->rows)
		{
			
			if (map->arr[row][col] > 0)
			{
				draw_square(image, 10, x, y, 0xFF0000FF);
			}
			row++;
			y += 10;
		}
		col++;
		x += 10;
	}
}
/*
void	draw_line(mlx_image_t *image, t_line line, uint32_t color)
{
	unsigned int	a;
	unsigned int	b;
	unsigned int	p;
	unsigned int	x;
	unsigned int	y;

	x = line.xa;
	y = line.ya;
	while (x <= line.xb)
	{
		a = 2 * (line.yb - line.ya);
		b = a - 2 * (line.xb - line.xa);
		p = a - (line.xb - line.xa);
		if (p < 0)
		{
			p += a;
		}
		else
		{
			y++;
			p += b;
		}
		mlx_put_pixel(image, x, y, color);
		x++;
	}
}
*/
// glory to Bresenham

void	draw_line(mlx_image_t *image, t_line line, uint32_t color)
{
	int	slope_error;
	int	new_slope_error;
	unsigned int	x;
	unsigned int	y;

	x = line.xa;
	y = line.ya;
	slope_error = 2 * (line.yb - line.ya);
	new_slope_error = slope_error - (line.xb - line.xa);
	while (x <= line.xb)
	{
		mlx_put_pixel(image, x, y, color);
		new_slope_error += slope_error;
		if (new_slope_error >= 0)
		{
			y++;
			new_slope_error -= 2 * (line.xb - line.xa);
		}
		x++;
	}
//	mlx_put_pixel(image, line.xa, line.ya, color);
//	mlx_put_pixel(image, line.xb, line.yb, color);
}

int	ft_draw(t_map *map, mlx_image_t *image)
{
	(void) map;
	set_all_pixels(image, 0x000000FF);
//	draw_square(image, 20, 40, 80, 0xFF0000FF);
	//draw_map_simple(map, image);
	t_line line;
	line.xa = 100;
	line.ya = 70;
	line.xb = 400;
	line.yb = 80;
	draw_line(image, line, 0xFF0000FF);
	return (0);
}

int	start_graphics(t_map *map)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	// value of assignement is value of left operand after assignement
	if (!(mlx = mlx_init(800, 600, "FdF", true)))
	{
		ft_printf("Error: failed mlx_init()\n");
		return (-1);
	}
	if (!(image = mlx_new_image(mlx, 800, 600)))
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
