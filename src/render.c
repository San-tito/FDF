/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:10:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/06 23:28:20 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clean_halt(t_scene *scene)
{
	lstclear(&(*scene).edges);
	perror("Error");
	exit(EXIT_FAILURE);
}

void	render_frame(void *param)
{
	mlx_t	*xlib;
	t_list	*edges;

	xlib = (*(t_scene *)param).xlib;
	edges = (*(t_scene *)param).edges;
	if (mlx_is_key_down(xlib, MLX_KEY_ESCAPE))
		mlx_close_window(xlib);
	if (mlx_is_key_down(xlib, MLX_KEY_UP))
		translate(edges, 0, -1);
	if (mlx_is_key_down(xlib, MLX_KEY_DOWN))
		translate(edges, 0, 1);
	if (mlx_is_key_down(xlib, MLX_KEY_LEFT))
		translate(edges, -1, 0);
	if (mlx_is_key_down(xlib, MLX_KEY_RIGHT))
		translate(edges, 1, 0);
	if (mlx_is_key_down(xlib, MLX_KEY_EQUAL))
		scale_factor((t_scene *)param, 1);
	if (mlx_is_key_down(xlib, MLX_KEY_MINUS))
		scale_factor((t_scene *)param, -1);
	draw_edges(param);
	ft_printf("Rendering \r");
}

void	render_wireframe(t_scene *scene)
{
	(*scene).xlib = mlx_init(WIDTH, HEIGHT, TITLE, true);
	(*scene).image = mlx_new_image((*scene).xlib, WIDTH, HEIGHT);
	mlx_image_to_window((*scene).xlib, (*scene).image, 0, 0);
	mlx_loop_hook((*scene).xlib, render_frame, scene);
	mlx_loop((*scene).xlib);
	mlx_terminate((*scene).xlib);
}
