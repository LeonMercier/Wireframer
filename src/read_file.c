/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:21:35 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/23 11:42:56 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// ft_split will sometimes result in a substring at the end that is just a
// newline. Checking if the substring starts with a digit gets rid of it.
static int	get_colnum(char *line)
{
	int		len;
	char	**strv;
	char	**orig_strv;

	len = 0;
	strv = ft_split(line, ' ');
	if (!strv)
	{
		free(line);
		return (-1);
	}
	orig_strv = strv;
	while (*strv)
	{
		if (!ft_isdigit(*strv[0]) && *strv[0] != '-' && *strv[0] != '+')
			break ;
		strv++;
		len++;
	}
	free_strv(orig_strv);
	return (len);
}

// shifting to the left and adding 255 adds the alpha channel at full opacity
static int	parse_color(char *str)
{
	int	color;
	int	word;

	color = 0;
	str += 2;
	while (*str)
	{
		word = hexchar_to_int(*str);
		if (word < 0 || word > 16)
			break ;
		color = (color * 16) + word;
		str++;
	}
	color = color << 8;
	color += 255;
	return (color);
}

static int	parse_point(t_map *map, char *point, int y, int x)
{
	char	**strv;
	int		err_atoi;

	strv = ft_split(point, ',');
	if (!strv)
		return (-1);
	err_atoi = 0;
	map->arr[y][x].depth = ft_atoi_safe2(strv[0], &err_atoi);
	if (err_atoi)
	{
		ft_printf("atoi error: %i\n", err_atoi);
		return (-1);
	}
	if (strv[1])
		map->arr[y][x].color = parse_color(strv[1]);
	else
		map->arr[y][x].color = 0xFFFFFFFF;
	free_strv(strv);
	return (0);
}

static int	parse_line(t_map *map, char *line)
{
	char	**strv;
	int		i;

	map->rows++;
	if (map_add_row(map) < 0)
		return (-1);
	strv = ft_split(line, ' ');
	if (!strv)
		return (-1);
	i = 0;
	while (i < map->cols)
	{
		if (parse_point(map, strv[i], map->rows - 1, i) == -1)
			return (-1);
		i++;
	}
	free_strv(strv);
	return (0);
}

int	read_file(t_map *map, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (map->rows == 0)
		{
			if (!line)
				return (-1);
			map->cols = get_colnum(line);
			if (map->cols < 0)
				return (-1);
		}
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
