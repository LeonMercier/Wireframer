/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:21:35 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/05 17:50:06 by lemercie         ###   ########.fr       */
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

static int	add_row_to_map(t_map *map)
{
	t_point	**new_arr;

	new_arr = (t_point **) malloc(sizeof(t_point *) * map->rows);
	if (!new_arr)
		return (-1);
	if (map->arr)
		ft_memmove(new_arr, map->arr, sizeof(t_point *) * (map->rows));
	new_arr[map->rows - 1] = (t_point *) malloc(sizeof(t_point *) * map->cols);
	map->arr = new_arr;
	return (0);
}

static int	parse_line(t_map *map, char *line)
{
	int		err_atoi;
	char	**strv;
	int		i;

	strv = ft_split(line, ' ');
	if (!strv)
		return (-1);
	map->cols = getlen_strv(strv); // assuming rectangular map, this would 
								   // really only need to be set once
	map->rows++;
	if (add_row_to_map(map) < 0)
	{
		//free strv
		return (-1);
	}
	i = 0;
	while (*strv) 
	{
		err_atoi = 0;
	//	ft_printf("%s-", *strv);
	//	ft_printf("%i ",  ft_atoi_safe2(*strv, &err_atoi));
//		ft_printf("%i ",  atoi(*strv));
		t_point	*point;
		point = (t_point *) malloc(sizeof(t_point));
		point->depth = ft_atoi_safe2(*strv, &err_atoi);
		map->arr[map->rows - 1][i] = point;
		if (err_atoi)
			ft_printf("atoi error: %i\n", err_atoi);
		strv++;
		i++;
	}
	//ft_printf("\n");
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
//		ft_printf("%s\n", line);
		if (parse_line(map, line) < 0)
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	close(fd);
	return (0);
}
