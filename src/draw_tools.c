/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:31:32 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/19 15:58:36 by lemercie         ###   ########.fr       */
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
    return ((rgba >> 24) & 0xFF);
}

// Get the green channel.
int get_g(int rgba)
{
    return ((rgba >> 16) & 0xFF);
}

// Get the blue channel.
int get_b(int rgba)
{
    return ((rgba >> 8) & 0xFF);
}

// Get the alpha channel.
int get_a(int rgba)
{
    return (rgba & 0xFF);
}

uint32_t	get_gradient(int dx, int dy, t_line line, uint32_t color_a,
		uint32_t color_b)
{
	double curlen_by_totlen;
	uint32_t		ret_color;

	ret_color = 0;
	curlen_by_totlen = (sqrt(pow((line.xb - line.xa), 2)
				+ pow((line.yb - line.ya), 2)))
				/ (sqrt((dy * dy) + (dx * dx)));
	ret_color += trunc((get_r(color_a) * curlen_by_totlen)
			+ (get_r(color_b) * (1 - curlen_by_totlen)));
	ret_color = ret_color << 8;
	ret_color += trunc((get_g(color_a) * curlen_by_totlen)
			+ (get_g(color_b) * (1 - curlen_by_totlen)));
	ret_color = ret_color << 8;
	ret_color += trunc((get_b(color_a) * curlen_by_totlen)
			+ (get_b(color_b) * (1 - curlen_by_totlen)));
	ret_color = ret_color << 8;
	ret_color += trunc((get_a(color_a) * curlen_by_totlen)
			+ (get_a(color_b) * (1 - curlen_by_totlen)));
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
		if (line.xa < 0 || (unsigned int) line.xa >= image->width ||
				line.ya < 0 || (unsigned int) line.ya >= image->height)
		{
			ft_printf("Error: pixel coords %i, %i out of bounds\n", line.ya,
					line.xa);
			break ;
		}
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
