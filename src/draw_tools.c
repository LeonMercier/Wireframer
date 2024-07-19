/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:31:32 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/19 10:25:05 by lemercie         ###   ########.fr       */
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

// Get the red channel.
int get_r(int rgba)
{
    // Move 3 bytes to the right and mask out the first byte.
    return ((rgba >> 24) & 0xFF);
}

// Get the green channel.
int get_g(int rgba)
{
    // Move 2 bytes to the right and mask out the first byte.
    return ((rgba >> 16) & 0xFF);
}

// Get the blue channel.
int get_b(int rgba)
{
    // Move 1 byte to the right and mask out the first byte.
    return ((rgba >> 8) & 0xFF);
}

// Get the alpha channel.
int get_a(int rgba)
{
    // Move 0 bytes to the right and mask out the first byte.
    return (rgba & 0xFF);
}

// TODO: check for division by zero
uint32_t	get_gradient(int dx, int dy, t_line line, uint32_t color_a,
		uint32_t color_b)
{
	double total_len;
	double current_len;
	unsigned char	channel_a;
	unsigned char	channel_b;
	unsigned char	channel_new;
	uint32_t		ret_color;

	total_len = sqrt((dy * dy) + (dx *dx));
	current_len = sqrt(pow((line.xb - line.xa), 2) +
			pow((line.yb - line.ya), 2));
	channel_a = get_r(color_a);
	channel_b = get_r(color_b);
	channel_new = trunc((channel_a * (current_len / total_len)) +
		(channel_b * (1 - (current_len / total_len))));
	ret_color = channel_new;
	ret_color = ret_color << 8;
	channel_a = get_g(color_a);
	channel_b = get_g(color_b);
	channel_new = trunc((channel_a * (current_len / total_len)) +
		(channel_b * (1 - (current_len / total_len))));
	ret_color += channel_new;
	ret_color = ret_color << 8;
	channel_a = get_b(color_a);
	channel_b = get_b(color_b);
	channel_new = trunc((channel_a * (current_len / total_len)) +
		(channel_b * (1 - (current_len / total_len))));
	ret_color += channel_new;
	ret_color = ret_color << 8;
	channel_a = get_a(color_a);
	channel_b = get_a(color_b);
	channel_new = trunc((channel_a * (current_len / total_len)) +
		(channel_b * (1 - (current_len / total_len))));
	ret_color += channel_new;
	return (ret_color);
}

// Bresenham's line algo
void	draw_line(mlx_image_t *image, t_line line, uint32_t color_a,
		uint32_t color_b)
{
	int	dx;
	int	dy;
	int				inc_x;
	int				inc_y;
	int	err;
	int	new_err;

	dx = abs(line.xb - line.xa);
	if (line.xa < line.xb)
		inc_x = 1;
	else
		inc_x = -1;
	dy = -1 * abs(line.yb - line.ya);
	if (line.ya < line.yb)
		inc_y = 1;
	else
		inc_y = -1;
	err = dx + dy;
	while (line.xa != line.xb || line.ya != line.yb)
	{
		mlx_put_pixel(image, line.xa, line.ya,
				get_gradient(dx, dy, line, color_a, color_b));
		new_err = 2 * err;
		if (new_err >= dy)
		{
			err += dy;
			line.xa += inc_x;
		}
		if (new_err <= dx)
		{
			err += dx;
			line.ya += inc_y;
		}
	}
}
