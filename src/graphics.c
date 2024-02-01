/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 07:43:56 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/01 08:49:45 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_xlib xlib, int x, int y, unsigned int color)
{
	float	offset;

	offset = (xlib.size_line * y) + (x * (xlib.bits_per_pixel / 8));
	*((unsigned int *)(xlib.img_addr) + (int)offset) = color;
}

void	draw_edges(t_scene *scene)
{
	t_list	*current;
	t_edge	*current_edge;

	current = (*scene).edges;
	while (current)
	{
		current_edge = (t_edge *)(current->content);
		pixel_put((*scene).xlib, (int)current_edge->x, (int)current_edge->y,
			current_edge->color);
		current = current->next;
	}
}
