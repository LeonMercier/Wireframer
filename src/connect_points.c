/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_points.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:48:25 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/16 11:25:07 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void connect_horizontally(t_map *map, mlx_image_t *image, int x, int y)
{
	t_line	line;
				
	line.xa = lround(map->arr[y][x].screen_x);
	line.ya = lround(map->arr[y][x].screen_y);
	line.xb = lround(map->arr[y][x + 1].screen_x);
	line.yb = lround(map->arr[y][x + 1].screen_y);
	draw_line(image, line, 0xFF0000FF);
}

static void connect_vertically(t_map *map, mlx_image_t *image, int x, int y)
{
	t_line	line;
				
	line.xa = lround(map->arr[y][x].screen_x);
	line.ya = lround(map->arr[y][x].screen_y);
	line.xb = lround(map->arr[y + 1][x].screen_x);
	line.yb = lround(map->arr[y + 1][x].screen_y);
	draw_line(image, line, 0xFF0000FF);
}

void	connect_points(t_map *map, mlx_image_t *image)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			if (x < map->cols - 1)
			{
				connect_horizontally(map, image, x, y);
			}
			if (y < map->rows - 1)
			{
				connect_vertically(map, image, x, y);
			}
			x++;
		}
		y++;
	}
}
