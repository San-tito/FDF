/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 07:43:56 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/14 19:45:35 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	pixel_put(mlx_image_t *image, size_t x, size_t y, size_t color)
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

static void	draw_line(mlx_image_t *image, t_point p0, t_point p1)
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
		pixel_put(image, p0.x, p0.y, get_color(p0.color, p1.color));
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
	float	sine;
	float	cosine;

	sine = sin((*scene).radians);
	cosine = cos((*scene).radians);
	p0.x = floor((float)(*e0).axis * (float)(*scene).scale * cosine
			- (float)(*e0).ordinate * (float)(*scene).scale * sine);
	p0.y = floor((float)(*e0).axis * (float)(*scene).scale * sine
			+ (float)(*e0).ordinate * (float)(*scene).scale * cosine);
	p0.color = (*e0).color;
	p1.x = floor((float)(*e1).axis * (float)(*scene).scale * cosine
			- (float)(*e1).ordinate * (float)(*scene).scale * sine);
	p1.y = floor((float)(*e1).axis * (float)(*scene).scale * sine
			+ (float)(*e1).ordinate * (float)(*scene).scale * cosine);
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
