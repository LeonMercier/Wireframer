/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:41:08 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/02 11:46:29 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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

int	add_row_to_map(t_map *map, int len)
{
	map->rows++;
	//realloc
}

int	parse_line(t_map *map, char *line)
{
	int		err_atoi;
	char	**strv;
	int		i;

	strv = ft_split(line, ' ');
	if (!strv)
		return (-1);
	map->cols = getlen_strv(strv);
	add_row_to_map(map, getlen_strv(strv));
	i = 0;
	while (*strv)
	{
		map->arr[map->rows - 1][i] = ft_atoi_safe(*strv, &err_atoi);
		strv++;
		i++;
	}

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
		if (parse_line(map, line) < 0)
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	return (0);
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
	read_file(&map, argv[1]);
	// one line becomes one int array
	// => 2D array, formatted as [y][x]
	// struct to store array, width and heigth
}
