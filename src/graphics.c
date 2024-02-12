/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 07:43:56 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/12 20:59:49 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(mlx_image_t *image, size_t x, size_t y, size_t color)
{
	int				i;
	unsigned char	*pixel;

	if (x < (*image).width && y < (*image).height)
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

void	draw_line(mlx_image_t *image, t_point p0, t_point p1)
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;

	dx = abs(p1.x - p0.x);
	sx = copysign(1, p1.x - p0.x);
	dy = -abs(p1.y - p0.y);
	sy = copysign(1, p1.y - p0.y);
	err = dx + dy;
	while (!(p0.x == p1.x && p0.y == p1.y))
	{
		pixel_put(image, p0.x, p0.y, p0.color);
		if (err * 2 >= dy)
		{
			err += dy;
			p0.x += sx;
		}
		if (err * 2 <= dx)
		{
			err += dx;
			p0.y += sy;
		}
	}
}

static void	draw_segment(t_scene *scene, t_edge *e0, t_edge *e1)
{
	t_point	p0;
	t_point	p1;

	p0.x = (*e0).axis * (*scene).scale;
	p0.y = (*e0).ordinate * (*scene).scale;
	p0.color = (*e0).color;
	p1.x = (*e1).axis * (*scene).scale;
	p1.y = (*e1).ordinate * (*scene).scale;
	p1.color = (*e1).color;
	draw_line((*scene).image, p0, p1);
}

static t_edge	*find_down(t_list *edges, t_edge *edge)
{
	t_list	*current;

	current = (*edges).next;
	while (current)
	{
		if ((*(t_edge *)((*current).content)).axis == (*edge).axis)
			return ((t_edge *)((*current).content));
		current = (*current).next;
	}
	return (NULL);
}

void	draw_edges(t_scene *scene)
{
	t_list	*current;
	t_edge	*edge;
	t_edge	*next;
	t_edge	*down;

	current = (*scene).edges;
	while (current && (*current).next)
	{
		edge = (t_edge *)((*current).content);
		next = (t_edge *)((*((*current).next)).content);
		if ((*edge).ordinate == (*next).ordinate)
			draw_segment(scene, edge, next);
		down = find_down(current, edge);
		if (down)
			draw_segment(scene, edge, down);
		current = (*current).next;
	}
}
