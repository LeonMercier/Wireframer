/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_isometric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:50:19 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/18 15:12:24 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// TODO get rid of magic numbers if possible
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
