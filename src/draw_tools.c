/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:31:32 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/08 11:31:08 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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
/*
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
*/
static int		ft_abs(int n)
{
	if (n >= 0)
		return (n);
	return (-n);
}

// Bresenham's line algo
void	draw_line(mlx_image_t *image, t_line line, uint32_t color)
{
	int	dx;
	int	dy;
	int				inc_x;
	int				inc_y;
	int	err;
	int	new_err;

	dx = ft_abs(line.xb - line.xa);
	if (line.xa < line.xb)
		inc_x = 1;
	else
		inc_x = -1;
	dy = -1 * ft_abs(line.yb - line.ya);
	if (line.ya < line.yb)
		inc_y = 1;
	else
		inc_y = -1;
	err = dx + dy;
	while (line.xa != line.xb || line.ya != line.yb)
	{
		mlx_put_pixel(image, line.xa, line.ya, color);
		new_err = 2 * err;
		if (new_err >= dy)
		{
			err += dy;
			line.xa += inc_x;
		}
		if (new_err <= dx)
		{
			err += dx;
			line.ya += inc_y;
		}
	}
}



