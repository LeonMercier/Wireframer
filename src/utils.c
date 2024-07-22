/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:13:44 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/22 17:03:06 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	free_map(t_map *map)
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

void	fdf_cleanup(t_map *map)
{
	free_map(map);
}

void	fdf_cleanup_exit(t_map *map)
{
	fdf_cleanup(map);
	exit(1);
}

int	hexchar_to_int(char c)
{
	const char	upper[] = {"0123456789ABCDEF"};
	const char	lower[] = {"0123456789abcdef"};
	int			i;

	i = 0;
	while (i < 16)
	{
		if (c == lower[i] || c == upper[i])
			return (i);
		i++;
	}
	return (-1);
}
