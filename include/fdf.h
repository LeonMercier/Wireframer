/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:04:23 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/04 14:30:14 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../lib/libft/libft.h"

typedef struct	s_map
{
	int **arr;
	int	cols;
	int	rows;
}	t_map;

typedef struct	s_line
{
	unsigned int	xa;
	unsigned int	ya;
	unsigned int	xb;
	unsigned int	yb;
}	t_line;

int	ft_atoi_safe2(const char *str, int *err_atoi);
// read_file.c
int	read_file(t_map *map, char *filename);
#endif
