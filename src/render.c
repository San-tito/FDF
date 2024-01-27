/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:10:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/01/27 21:16:39 by sguzman          ###   ########.fr       */
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
	*((unsigned int *)(offset + (*mlx).img_addr)) = color;
}

void	draw_line(t_mlx *mlx, t_edge edge0, t_edge edge1)
{
	float	delta_x;
	float	delta_y;
	float	step;
	int		color;
	float	x_increment;
	float	y_increment;
	float	x;
	float	y;

	delta_x = edge1.x - edge0.x;
	delta_y = edge1.y - edge0.y;
	color = edge0.color;
	if (fabs(delta_x) > fabs(delta_y))
		step = fabs(delta_x);
	else
		step = fabs(delta_y);
	x_increment = delta_x / step;
	y_increment = delta_y / step;
	x = edge0.x;
	y = edge0.y;
	for (int i = 0; i <= step; i++)
	{
		pixel_put(mlx, round(x), round(y), color);
		x += x_increment;
		y += y_increment;
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
		draw_line(mlx, *current_edge, *next_edge);
		current = current->next;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr,
		(SCREEN_WIDTH - SCREEN_WIDTH) / 2, (SCREEN_HEIGHT - SCREEN_HEIGHT) / 2);
}

void	render_wireframe(t_list **edges, t_mlx *mlx)
{
	(*mlx).mlx_ptr = mlx_init();
	if (!(*mlx).mlx_ptr)
		clean_halt(edges, mlx);
	(*mlx).win_ptr = mlx_new_window((*mlx).mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT,
			"FDF!");
	if (!(*mlx).win_ptr)
		clean_halt(edges, mlx);
	//(*mlx).img_ptr = mlx_new_image((*mlx).mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	(*mlx).img_ptr = 0;
	if (!(*mlx).img_ptr)
		clean_halt(edges, mlx);
	(*mlx).img_addr = mlx_get_data_addr((*mlx).img_ptr, &(*mlx).bits_per_pixel,
			&(*mlx).size_line, &(*mlx).endian);
	render_edges(*edges, mlx);
	mlx_loop((*mlx).mlx_ptr);
}
