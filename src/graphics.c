/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 07:43:56 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/07 22:20:28 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(mlx_image_t *image, int x, int y, int color)
{
	unsigned char	*pixel;

	if (x > (int)(*image).width || x < 0 || y < 0 || y > (int)(*image).height)
		return ;
	pixel = (*image).pixels + (y * (*image).width + x) * sizeof(int);
	*pixel++ = (color >> 24);
	*pixel++ = (color >> 16);
	*pixel++ = (color >> 8);
	*pixel++ = (color & 0xFFFFFF);
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

	x0 = ((*p0).x * (*scene).scale);
	y0 = ((*p0).y * (*scene).scale);
	x1 = ((*p1).x * (*scene).scale);
	y1 = ((*p1).y * (*scene).scale);
	dx = abs(x1 - x0);
	sx = x0 < x1 ? 1 : -1;
	dy = -abs(y1 - y0);
	sy = y0 < y1 ? 1 : -1;
	err = dx + dy;
	while (42)
	{
		pixel_put((*scene).image, x0, y0, (*p0).color);
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

t_edge	*find_down(t_list *edges, t_edge *edge)
{
	t_list	*current;

	current = (*edges).next;
	while (current)
	{
		if ((*(t_edge *)((*current).content)).x == (*edge).x)
			return ((t_edge *)((*current).content));
		current = (*current).next;
	}
	return (NULL);
}

void	draw_edges(t_scene *scene)
{
	t_list	*current;
	t_edge	*current_edge;
	t_edge	*next_edge;
	t_edge	*down_edge;

	current = (*scene).edges;
	while (current && (*current).next)
	{
		current_edge = (t_edge *)((*current).content);
		next_edge = (t_edge *)((*((*current).next)).content);
		if ((*current_edge).y == (*next_edge).y)
			draw_line(scene, current_edge, next_edge);
		down_edge = find_down(current, current_edge);
		if (down_edge)
			draw_line(scene, current_edge, down_edge);
		current = (*current).next;
	}
}
