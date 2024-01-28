/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:10:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/01/28 23:26:36 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	clean_halt(t_scene *scene)
{
	xlibclear(&(*scene).xlib);
	lstclear(&(*scene).edges);
	exit(EXIT_FAILURE);
}

void	pixel_put(t_xlib xlib, float x, float y, unsigned int color)
{
	float	offset;

	offset = (xlib.size_line * y) + (x * (xlib.bits_per_pixel / 8));
	*((unsigned int *)(xlib.img_addr) + (int)offset) = color;
}

void	draw_line(t_xlib *mlx, t_edge *p0, t_edge *p1)
{
	const float	dx = fabsf(p1->x - p0->x);
	const float	sx = (p0->x < p1->x) ? 1.0f : -1.0f;
	const float	dy = -fabsf(p1->y - p0->y);
	const float	sy = (p0->y < p1->y) ? 1.0f : -1.0f;
	float		error;
	float		e2;

	error = dx + dy;
	while (1)
	{
		pixel_put(*mlx, p0->x, p0->y, p0->color);
		if (p0->x == p1->x && p0->y == p1->y)
			break ;
		e2 = 2.0f * error;
		if (e2 >= dy)
		{
			if (p0->x == p1->x)
				break ;
			error += dy;
			p0->x += sx;
		}
		if (e2 <= dx)
		{
			if (p0->y == p1->y)
				break ;
			error += dx;
			p0->y += sy;
		}
	}
}

int	key_event(int keycode, t_scene *scene)
{
	ft_printf("Pressed %d\n", keycode);
	(*scene).scale += 2;
	return (1);
}

int	render_edges(t_scene *scene)
{
	t_list	*current;
	t_edge	*current_edge;
	t_edge	*next_edge;
	t_xlib	*xlib;

	xlib = &(*scene).xlib;
	current = (*scene).edges;
	while (current && current->next)
	{
		current_edge = (t_edge *)(current->content);
		next_edge = (t_edge *)(current->next->content);
		draw_line(&(*scene).xlib, current_edge, next_edge);
		current = current->next;
	}
	mlx_put_image_to_window((*xlib).mlx_ptr, (*xlib).win_ptr, (*xlib).img_ptr,
		(WIDTH - WIDTH) / 2, (HEIGHT - HEIGHT) / 2);
	ft_printf("Rendering \r");
	return (0);
}

void	render_wireframe(t_scene *scene)
{
	t_xlib	*xlib;

	xlib = &(*scene).xlib;
	(*xlib).mlx_ptr = mlx_init();
	if (!(*xlib).mlx_ptr)
		clean_halt(scene);
	(*xlib).win_ptr = mlx_new_window((*xlib).mlx_ptr, WIDTH, HEIGHT, TITLE);
	if (!(*xlib).win_ptr)
		clean_halt(scene);
	(*xlib).img_ptr = mlx_new_image((*xlib).mlx_ptr, WIDTH, HEIGHT);
	if (!(*xlib).img_ptr)
		clean_halt(scene);
	(*xlib).img_addr = mlx_get_data_addr((*xlib).img_ptr,
			&(*xlib).bits_per_pixel, &(*xlib).size_line, &(*xlib).endian);
	mlx_key_hook((*xlib).win_ptr, key_event, scene);
	mlx_loop_hook((*xlib).mlx_ptr, render_edges, scene);
	mlx_loop((*xlib).mlx_ptr);
}
