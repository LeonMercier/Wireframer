/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_top_left.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:51:51 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/16 17:14:00 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"


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
