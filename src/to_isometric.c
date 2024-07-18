/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_isometric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:50:19 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/18 17:21:30 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// degrees * (PI / 180) = radians
void	to_isometric(t_map *map)
{
	int	y;
	int	x;
	double	angle;
	double	axis_angle;

	y = 0;
	angle = 30 * (M_PI / 180);
	axis_angle = 120 * (M_PI / 180);
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			map->arr[y][x].screen_x =
				(x * cos(angle)) +
				 (y * cos(angle + axis_angle)) +
				 (map->arr[y][x].depth * cos(angle - axis_angle));
			map->arr[y][x].screen_y =
				(x * sin(angle)) +
				 (y * sin(angle + axis_angle)) + 
				 (map->arr[y][x].depth * sin(angle - axis_angle));
			x++;
		}
		y++;
	}
}
