/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:10:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/07 16:37:40 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clean_halt(t_scene *scene)
{
	mlx_close_window((*scene).xlib);
	lstclear(&(*scene).edges);
	perror("Error");
	exit(EXIT_FAILURE);
}

void	render_frame(void *param)
{
	mlx_t		*xlib;
	t_scene		*scene;
	t_list		*edges;
	mlx_image_t	*image;

	scene = (t_scene *)param;
	xlib = (*scene).xlib;
	edges = (*scene).edges;
	image = (*scene).image;
	if (mlx_is_key_down(xlib, MLX_KEY_ESCAPE))
		mlx_close_window(xlib);
	if (mlx_is_key_down(xlib, MLX_KEY_UP) || mlx_is_key_down(xlib, MLX_KEY_W))
		translate(edges, 0, -1);
	if (mlx_is_key_down(xlib, MLX_KEY_DOWN) || mlx_is_key_down(xlib, MLX_KEY_S))
		translate(edges, 0, 1);
	if (mlx_is_key_down(xlib, MLX_KEY_LEFT) || mlx_is_key_down(xlib, MLX_KEY_A))
		translate(edges, -1, 0);
	if (mlx_is_key_down(xlib, MLX_KEY_RIGHT) || mlx_is_key_down(xlib,
			MLX_KEY_D))
		translate(edges, 1, 0);
	if (mlx_is_key_down(xlib, MLX_KEY_EQUAL))
		scale_factor(scene, 1);
	if (mlx_is_key_down(xlib, MLX_KEY_MINUS))
		scale_factor(scene, -1);
	ft_bzero((*image).pixels, (*image).width * (*image).height * sizeof(int));
	draw_edges(param);
	ft_printf("Rendering \r");
}

void	render_wireframe(t_scene *scene)
{
	(*scene).xlib = mlx_init(WIDTH, HEIGHT, TITLE, true);
	if (!(*scene).xlib)
		return (clean_halt(scene));
	(*scene).image = mlx_new_image((*scene).xlib, WIDTH, HEIGHT);
	if (!(*scene).image)
		return (clean_halt(scene));
	if (mlx_image_to_window((*scene).xlib, (*scene).image, 0, 0) < 0)
		return (clean_halt(scene));
	mlx_loop_hook((*scene).xlib, render_frame, scene);
	mlx_loop((*scene).xlib);
	mlx_terminate((*scene).xlib);
}
