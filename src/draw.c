/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:18:41 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/03 14:11:19 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	apply_translation(t_vector *v, int tx, int ty)
{
	(*v).i += tx;
	(*v).j += ty;
}

static void	apply_rotation(t_vector *v, float angle_x, float angle_y)
{
	const float	cos_x = cos(angle_x / 10);
	const float	sin_x = sin(angle_x / 10);
	const float	cos_y = cos(angle_y / 10);
	const float	sin_y = sin(angle_y / 10);
	const float	j_temp = v->j;
	const float	i_temp = v->i;

	v->j = j_temp * cos_x - v->i * sin_x;
	v->i = j_temp * sin_x + v->i * cos_x;
	v->i = i_temp * cos_y - v->j * sin_y;
	v->j = i_temp * sin_y + v->j * cos_y;
}

static void	draw_segment(t_scene *scene, t_edge *e0, t_edge *e1)
{
	t_vector	v0;
	t_vector	v1;
	const float	scale = (*scene).scale;
	const float	sine = sin((*scene).angle);
	const float	cosine = cos((*scene).angle);

	if ((*scene).view)
	{
		v0.i = ((*e0).axis - (*e0).ordinate) * cosine * scale;
		v0.j = (((*e0).axis + (*e0).ordinate) * sine - (*e0).altitude) * scale;
		v1.i = ((*e1).axis - (*e1).ordinate) * cosine * scale;
		v1.j = (((*e1).axis + (*e1).ordinate) * sine - (*e1).altitude) * scale;
	}
	else
	{
		v0.i = (*e0).axis * cosine * scale;
		v0.j = (*e0).ordinate * sine * scale;
		v1.i = (*e1).axis * cosine * scale;
		v1.j = (*e1).ordinate * sine * scale;
	}
	apply_rotation(&v0, (*scene).rotation.i, (*scene).rotation.j);
	apply_rotation(&v1, (*scene).rotation.i, (*scene).rotation.j);
	apply_translation(&v0, (*scene).translation.i, (*scene).translation.j);
	apply_translation(&v1, (*scene).translation.i, (*scene).translation.j);
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
