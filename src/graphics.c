/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 07:43:56 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/23 18:25:37 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	pixel_put(mlx_image_t *image, int x, int y, int color)
{
	int				i;
	unsigned char	*pixel;

	if ((unsigned)x < (*image).width && (unsigned)y < (*image).height)
	{
		pixel = (*image).pixels + (y * (*image).width + x) * sizeof(int);
		i = sizeof(int) * 6;
		while (i >= 0)
		{
			*pixel++ = (color >> i) & 0xFF;
			i -= sizeof(int) * 2;
		}
	}
}

void	draw_line(mlx_image_t *image, t_vector v0, t_vector v1, int color)
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;

	dx = abs(v1.i - v0.i);
	sx = (v0.i < v1.i) + (v0.i > v1.i) * -1;
	dy = -abs(v1.j - v0.j);
	sy = (v0.j < v1.j) + (v0.j > v1.j) * -1;
	err = dx + dy;
	while (!(v0.i == v1.i && v0.j == v1.j))
	{
		pixel_put(image, v0.i, v0.j, color);
		if (2 * err >= dy && v0.i != v1.i)
		{
			err += dy;
			v0.i += sx;
		}
		if (2 * err <= dx && v0.j != v1.j)
		{
			err += dx;
			v0.j += sy;
		}
	}
}
