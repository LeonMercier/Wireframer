/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:31:32 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/23 10:21:46 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	set_all_pixels(mlx_image_t *image, uint32_t color)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < image->width)
	{
		j = 0;
		while (j < image->height)
		{
			mlx_put_pixel(image, i, j, color);
			j++;
		}
		i++;
	}
}

static int	get_channel(int rgba, char channel)
{
	if (channel == 'r')
		return ((rgba >> 24) & 0xFF);
	if (channel == 'g')
		return ((rgba >> 16) & 0xFF);
	if (channel == 'b')
		return ((rgba >> 8) & 0xFF);
	if (channel == 'a')
		return (rgba & 0xFF);
	return (0);
}

static uint32_t	get_gradient(t_line line)
{
	double		curlen_by_totlen;
	uint32_t	ret_color;

	ret_color = 0;
	curlen_by_totlen = (sqrt(pow((line.xb - line.xa), 2)
				+ pow((line.yb - line.ya), 2)))
		/ (sqrt((line.dy * line.dy) + (line.dx * line.dx)));
	ret_color += trunc((get_channel(line.color_a, 'r') * curlen_by_totlen)
			+ (get_channel(line.color_b, 'r') * (1 - curlen_by_totlen)));
	ret_color = ret_color << 8;
	ret_color += trunc((get_channel(line.color_a, 'g') * curlen_by_totlen)
			+ (get_channel(line.color_b, 'g') * (1 - curlen_by_totlen)));
	ret_color = ret_color << 8;
	ret_color += trunc((get_channel(line.color_a, 'b') * curlen_by_totlen)
			+ (get_channel(line.color_b, 'b') * (1 - curlen_by_totlen)));
	ret_color = ret_color << 8;
	ret_color += trunc((get_channel(line.color_a, 'a') * curlen_by_totlen)
			+ (get_channel(line.color_b, 'a') * (1 - curlen_by_totlen)));
	return (ret_color);
}

static void	draw_line_loop(mlx_image_t *image, t_line line)
{
	int	err;
	int	new_err;

	err = line.dx + line.dy;
	while (line.xa != line.xb || line.ya != line.yb)
	{
		if (line.xa < 0 || (unsigned int) line.xa >= image->width
			|| line.ya < 0 || (unsigned int) line.ya >= image->height)
			break ;
		mlx_put_pixel(image, line.xa, line.ya, get_gradient(line));
		new_err = 2 * err;
		if (new_err >= line.dy)
		{
			err += line.dy;
			line.xa += line.inc_x;
		}
		if (new_err <= line.dx)
		{
			err += line.dx;
			line.ya += line.inc_y;
		}
	}
}

// Bresenham's line algo
void	draw_line(mlx_image_t *image, t_line line)
{
	line.dx = abs(line.xb - line.xa);
	if (line.xa < line.xb)
		line.inc_x = 1;
	else
		line.inc_x = -1;
	line.dy = -1 * abs(line.yb - line.ya);
	if (line.ya < line.yb)
		line.inc_y = 1;
	else
		line.inc_y = -1;
	draw_line_loop(image, line);
}
