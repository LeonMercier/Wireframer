/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:13:44 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/19 16:51:45 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	free_map(t_map *map)
{
	int	i;

	if (map->arr)
	{
		i = 0;
		while (i < map->rows)
		{
			if (map->arr[i])
				free(map->arr[i]);
			i++;
		}
		free(map->arr);
	}
}

void	fdf_cleanup(t_map *map, char *line)
{
	free(line);
	free_map(map);
}

void	fdf_cleanup_exit(t_map *map, char *line)
{
	fdf_cleanup(map, line);
	exit(-1);
}
