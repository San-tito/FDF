/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:18:41 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/04 13:14:00 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	translation(t_vector *v, int tx, int ty)
{
	(*v).i += tx;
	(*v).j += ty;
}

static void	rotation(t_edge *edge, t_vector angle)
{
	(void)edge;
	(void)angle;
}

static void	draw_segment(t_scene *scene, t_edge *e0, t_edge *e1)
{
	t_vector	v0;
	t_vector	v1;
	const float	scale = (*scene).scale;
	const float	sine = sin((*scene).angle);
	const float	cosine = cos((*scene).angle);

	rotation(e0, (*scene).rotation);
	rotation(e1, (*scene).rotation);
	if ((*scene).view)
	{
		v0.i = ((*e0).axis - (*e0).ordinate) * cosine * scale;
		v0.j = (((*e0).axis + (*e0).ordinate) * sine - (*e0).altitude) * scale;
		v1.i = ((*e1).axis - (*e1).ordinate) * cosine * scale;
		v1.j = (((*e1).axis + (*e1).ordinate) * sine - (*e1).altitude) * scale;
	}
	else
	{
		v0.i = ((*e0).axis + (*e0).altitude) * cosine * scale;
		v0.j = ((*e0).ordinate + (*e0).altitude) * sine * scale;
		v1.i = ((*e1).axis + (*e1).altitude) * cosine * scale;
		v1.j = ((*e1).ordinate + (*e1).altitude) * sine * scale;
	}
	translation(&v0, (*scene).translation.i, (*scene).translation.j);
	translation(&v1, (*scene).translation.i, (*scene).translation.j);
	draw_line((*scene).image, v0, v1, (*e0).color);
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
