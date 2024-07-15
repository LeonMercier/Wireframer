/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_top_left.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:51:51 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/15 15:03:34 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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
