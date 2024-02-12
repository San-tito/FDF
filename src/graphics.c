/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 07:43:56 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/12 16:58:07 by sguzman          ###   ########.fr       */
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
	t_edge	*current_edge;
	t_edge	*next_edge;
	t_edge	*down_edge;

	current = (*scene).edges;
	while (current && (*current).next)
	{
		current_edge = (t_edge *)((*current).content);
		next_edge = (t_edge *)((*((*current).next)).content);
		if ((*current_edge).ordinate == (*next_edge).ordinate)
			draw_line((*scene).image, (t_point){current_edge->axis
				* (*scene).scale, current_edge->ordinate * (*scene).scale,
				current_edge->color}, (t_point){next_edge->axis
				* (*scene).scale, next_edge->ordinate * (*scene).scale,
				next_edge->color});
		down_edge = find_down(current, current_edge);
		if (down_edge)
			draw_line((*scene).image, (t_point){current_edge->axis
				* (*scene).scale, current_edge->ordinate * (*scene).scale,
				current_edge->color}, (t_point){down_edge->axis
				* (*scene).scale, down_edge->ordinate * (*scene).scale,
				down_edge->color});
		current = (*current).next;
	}
}
