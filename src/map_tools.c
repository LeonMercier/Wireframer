/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:55:12 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/16 16:56:40 by lemercie         ###   ########.fr       */
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

void	get_max_coords(t_map *map, t_point *max)
{
	int	y;
	int	x;

	max->screen_x = map->arr[0][0].screen_x;
	max->screen_y = map->arr[0][0].screen_y;
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			if (map->arr[y][x].screen_x > max->screen_x)
				max->screen_x = map->arr[y][x].screen_x;
			if (map->arr[y][x].screen_y > max->screen_y)
				max->screen_y = map->arr[y][x].screen_y;
			x++;
		}
		y++;
	}	
}
