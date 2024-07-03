/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:21:35 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/03 14:41:09 by lemercie         ###   ########.fr       */
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
	int	**new_arr;

	new_arr = (int **) malloc(sizeof(int *) * map->rows);
	if (!new_arr)
		return (-1);
	if (map->arr)
		ft_memmove(new_arr, map->arr, sizeof(int *) * (map->rows));
	new_arr[map->rows - 1] = (int *) malloc(sizeof(int) * map->cols);
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
		map->arr[map->rows - 1][i] = ft_atoi_safe2(*strv, &err_atoi);
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
