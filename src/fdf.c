/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:41:08 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/03 12:37:00 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <stdlib.h> //dbugging
int	getlen_strv(char **strv)
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

int	add_row_to_map(t_map *map)
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

int	parse_line(t_map *map, char *line)
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
	//	ft_printf("%s-", *strv);
	//	ft_printf("%i ",  ft_atoi_safe2(*strv, &err_atoi));
	//	ft_printf("%i ",  atoi(*strv));
		map->arr[map->rows - 1][i] = ft_atoi_safe2(*strv, &err_atoi);
		strv++;
		i++;
	}
	ft_printf("\n");
	return (0);
}

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

void	print_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			ft_printf("%i ", map->arr[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc == 1)
	{
		ft_printf("Error: Filename missing\n");
		return (1);
	}
	if (argc > 2)
	{
		ft_printf("Error: Too many arguments\n");
		return (1);
	}
	map.arr = 0;
/*
	(void) argv;
	(void) map;
	int	test = 0;
	ft_printf("%i\n", ft_atoi_safe(" 10 ", &test));
*/
	read_file(&map, argv[1]);
	print_map(&map);
	// one line becomes one int array
	// => 2D array, formatted as [y][x]
	// struct to store array, width and heigth
}
