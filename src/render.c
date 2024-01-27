/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:10:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/01/27 23:05:20 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	clean_halt(t_list **edges, t_mlx *mlx)
{
	mlxclear(mlx);
	lstclear(edges);
	exit(EXIT_FAILURE);
}

void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	int	offset;

	offset = ((*mlx).size_line * y) + (x * ((*mlx).bits_per_pixel / 8));
	*((unsigned int *)((*mlx).img_addr) + offset) = color;
}

void	draw_line(t_mlx *mlx, t_edge *p0, t_edge *p1)
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
		pixel_put(mlx, p0->x, p0->y, p0->color);
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

void	render_edges(t_list *edges, t_mlx *mlx)
{
	t_list	*current;
	t_edge	*current_edge;
	t_edge	*next_edge;

	current = edges;
	while (current && current->next)
	{
		current_edge = (t_edge *)(current->content);
		next_edge = (t_edge *)(current->next->content);
		draw_line(mlx, current_edge, next_edge);
		current = current->next;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, (WIDTH
			- WIDTH) / 2, (HEIGHT - HEIGHT) / 2);
}

void	render_wireframe(t_list **edges, t_mlx *mlx)
{
	(*mlx).mlx_ptr = mlx_init();
	if (!(*mlx).mlx_ptr)
		clean_halt(edges, mlx);
	(*mlx).win_ptr = mlx_new_window((*mlx).mlx_ptr, WIDTH, HEIGHT, TITLE);
	if (!(*mlx).win_ptr)
		clean_halt(edges, mlx);
	(*mlx).img_ptr = mlx_new_image((*mlx).mlx_ptr, WIDTH, HEIGHT);
	if (!(*mlx).img_ptr)
		clean_halt(edges, mlx);
	(*mlx).img_addr = mlx_get_data_addr((*mlx).img_ptr, &(*mlx).bits_per_pixel,
			&(*mlx).size_line, &(*mlx).endian);
	render_edges(*edges, mlx);
	mlx_loop((*mlx).mlx_ptr);
}
