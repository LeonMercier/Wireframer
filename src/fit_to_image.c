/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fit_to_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:44:11 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/19 16:46:04 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// handles both zooming in and zooming out
void	fit_to_image(t_map *map, int image_width, int image_heigth)
{
	t_point	min;
	t_point	max;
	double	zoomfactor_y;
	double	zoomfactor_x;

	get_min_coords(map, &min);
	get_max_coords(map, &max);
	zoomfactor_y = fabs(max.screen_y - min.screen_y) / image_heigth;
	zoomfactor_x = fabs(max.screen_x - min.screen_x) / image_width;
	if (zoomfactor_y <= 0 || zoomfactor_x <= 0)
		return ;
	ft_zoom(map, fmin(1 / zoomfactor_y, 1 / zoomfactor_x));
}
