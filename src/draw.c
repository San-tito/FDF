/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:18:41 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/23 18:54:07 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

static void	draw_segment(t_scene *scene, t_edge *e0, t_edge *e1)
{
	t_vector	v0;
	t_vector	v1;
	const float	scale = (*scene).scale;
	const float	sine = sin((*scene).angle);
	const float	cosine = cos((*scene).angle);

	v0.i = ((*e0).axis - (*e0).ordinate) * cosine * scale;
	v0.j = (((*e0).axis + (*e0).ordinate) * sine - (*e0).altitude) * scale;
	v1.i = ((*e1).axis - (*e1).ordinate) * cosine * scale;
	v1.j = (((*e1).axis + (*e1).ordinate) * sine - (*e1).altitude) * scale;
	v0.i += (*scene).translation.i;
	v0.j += (*scene).translation.j;
	v1.i += (*scene).translation.i;
	v1.j += (*scene).translation.j;
	draw_line((*scene).image, v0, v1, get_color((*e0).color, (*e1).color));
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
