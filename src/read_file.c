/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:21:35 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/19 12:25:27 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// ft_split will sometimes result in a substring at the end that is just a
// newline. Checking if the substring starts with a digit gets rid of it.
static int	get_colnum(char *line)
{
	int	len;
	char	**strv;

	len = 0;
	strv = ft_split(line, ' ');
	if (!strv)
		return (-1);
	while (*strv)
	{
		if (!ft_isdigit(*strv[0]) && *strv[0] != '-' && *strv[0] != '+')
			break ;
		strv++;
		len++;
	}
	return (len);
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

// shifting to the left and adding 255 adds the alpha channel at full opacity
int	parse_color(char *str)
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

// the second call to ft_split get rid of the newlines of the last column
int	parse_point(t_map *map, char *point, int y, int x)
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
	return (0);
}

static int	parse_line(t_map *map, char *line)
{
	char	**strv;
	int		i;
	t_point **new_arr;

	strv = ft_split(line, ' ');
	if (!strv)
		return (-1);
	map->rows++;
	new_arr = malloc(map->rows  * sizeof(t_point *));
	if (!new_arr)
		return (-1);
	if (map->arr)
		ft_memmove(new_arr, map->arr, sizeof(t_point *) * (map->rows - 1));
	free(map->arr);
	map->arr = new_arr;
	map->arr[map->rows - 1] = malloc(map->cols * sizeof(t_point));
	if (!map->arr[map->rows - 1])
		return (-1);
	i = 0;
	while (i < map->cols) 
	{
		if (parse_point(map, *strv, map->rows - 1, i) == -1)
			return (-1);
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
	if (fd < 0)
	{
		ft_printf("Error: Could not open file\n");
		return (-1);
	}
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (-1);
	}
	map->cols = get_colnum(line);
	if (map->cols == -1)
	{
		free(line);
		close(fd);
		return (-1);
	}
	while (line)
	{
		if (parse_line(map, line) < 0)
		{
			ft_printf("Error in parse_line()\n");
			close(fd);
			fdf_cleanup_exit(map, line);
			return (-1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
