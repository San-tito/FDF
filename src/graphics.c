/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 07:43:56 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/06 23:40:06 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	pixel_put(mlx_image_t image, unsigned int x, unsigned int y,
		unsigned int color)
{
	char	*pixel;
	int		i;

	i = *(int *)image.pixels - 8;
	pixel = image.context + ((image.count * y) + (x * (*(int *)image.pixels
					/ 8)));
	while (i >= 0)
	{
		if (image.enabled != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (*(int *)image.pixels - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	draw_line(t_scene *scene, t_edge *p0, t_edge *p1)
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;

	x0 = (p0->x * scene->scale);
	y0 = (p0->y * scene->scale);
	x1 = (p1->x * scene->scale);
	y1 = (p1->y * scene->scale);
	dx = abs(x1 - x0);
	sx = x0 < x1 ? 1 : -1;
	dy = -abs(y1 - y0);
	sy = y0 < y1 ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		pixel_put(*(*scene).image, x0, y0, p0->color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_edges(t_scene *scene)
{
	t_list	*current;
	t_edge	*current_edge;
	t_edge	*next_edge;

	current = (*scene).edges;
	while (current && (*current).next)
	{
		current_edge = (t_edge *)((*current).content);
		next_edge = (t_edge *)((*((*current).next)).content);
		draw_line(scene, current_edge, next_edge);
		current = (*current).next;
	}
}
