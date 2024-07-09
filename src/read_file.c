/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:21:35 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/09 14:41:43 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	getlen_strv(char **strv)
{
	int	len;

	len = 0;
	while (*strv)
	{
		strv++;
		len++;
	}
	return (len);
}

static int	parse_line(t_map *map, char *line)
{
	int		err_atoi;
	char	**strv;
	int		i;
	t_point **new_arr;

	strv = ft_split(line, ' ');
	if (!strv)
		return (-1);
	map->cols = getlen_strv(strv); // assuming rectangular map, this would 
								   // really only need to be set once
	map->rows++;
	new_arr = malloc(map->rows  * sizeof(t_point *));
	if (map->arr)
		ft_memmove(new_arr, map->arr, sizeof(t_point *) * (map->rows - 1));
	map->arr = new_arr;
	map->arr[map->rows - 1] = malloc(map->cols * sizeof(t_point));
	i = 0;
	while (*strv) 
	{
		// TODO> are the two lines here needed?
		map->arr[map->rows - 1][i].screen_x = 0;
		map->arr[map->rows - 1][i].screen_y = 0;
		map->arr[map->rows - 1][i].depth = ft_atoi_safe2(*strv, &err_atoi);
		err_atoi = 0;
		if (err_atoi)
			ft_printf("atoi error: %i\n", err_atoi);
		strv++;
		i++;
	}
	return (0);
}

// TODO: do we know whether GNL has reached EOF or failed internally?
int	read_file(t_map *map, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (parse_line(map, line) < 0)
		{
			ft_printf("Error in parse_line()\n");
			free(line);
			return (-1);
		}
		free(line);
	}
	close(fd);
	return (0);
}
