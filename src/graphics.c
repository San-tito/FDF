/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 07:43:56 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/23 00:49:32 by sguzman          ###   ########.fr       */
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

static int	get_color(int start_color, int end_color)
{
	int	r;
	int	g;
	int	b;

	r = (start_color >> 16) & 0xFF;
	g = (start_color >> 8) & 0xFF;
	b = end_color & 0xFF;
	return ((r << 16) | (g << 8) | b);
}

static void	draw_line(mlx_image_t *image, t_point p0, t_point p1, int color)
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;

	dx = abs(p1.x - p0.x);
	sx = (p0.x < p1.x) + (p0.x > p1.x) * -1;
	dy = -abs(p1.y - p0.y);
	sy = (p0.y < p1.y) + (p0.y > p1.y) * -1;
	err = dx + dy;
	while (!(p0.x == p1.x && p0.y == p1.y))
	{
		pixel_put(image, p0.x, p0.y, color);
		if (2 * err >= dy && p0.x != p1.x)
		{
			err += dy;
			p0.x += sx;
		}
		if (2 * err <= dx && p0.y != p1.y)
		{
			err += dx;
			p0.y += sy;
		}
	}
}

void	draw_segment(t_scene *scene, t_edge *e0, t_edge *e1)
{
	t_point		p0;
	t_point		p1;
	const float	scale = (*scene).scale;
	const float	sine = sin((*scene).angle);
	const float	cosine = cos((*scene).angle);

	p0.x = ((*e0).axis - (*e0).ordinate) * cosine * scale;
	p0.y = (((*e0).axis + (*e0).ordinate) * sine - (*e0).altitude) * scale;
	p1.x = ((*e1).axis - (*e1).ordinate) * cosine * scale;
	p1.y = (((*e1).axis + (*e1).ordinate) * sine - (*e1).altitude) * scale;
	p0.x += (*scene).translation.x;
	p0.y += (*scene).translation.y;
	p1.x += (*scene).translation.x;
	p1.y += (*scene).translation.y;
	draw_line((*scene).image, p0, p1, get_color((*e0).color, (*e1).color));
}

t_edge	*find_down(t_list *edges, t_edge *edge)
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
