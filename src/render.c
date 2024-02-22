/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:10:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/22 15:36:01 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clean_halt(t_scene *scene)
{
	mlx_close_window((*scene).xlib);
	mlx_terminate((*scene).xlib);
	lstclear(&(*scene).edges);
	perror("Error");
	exit(EXIT_FAILURE);
}

void	key_hook(t_scene *scene)
{
	mlx_t	*xlib;
	t_list	*edges;

	xlib = (*scene).xlib;
	edges = (*scene).edges;
	if (mlx_is_key_down(xlib, MLX_KEY_ESCAPE))
		mlx_close_window(xlib);
	if (mlx_is_key_down(xlib, MLX_KEY_EQUAL))
		zoom(scene, 1);
	if (mlx_is_key_down(xlib, MLX_KEY_MINUS))
		zoom(scene, -1);
	if (mlx_is_key_down(xlib, MLX_KEY_UP) || mlx_is_key_down(xlib, MLX_KEY_W))
		translate(edges, 0, -1);
	if (mlx_is_key_down(xlib, MLX_KEY_DOWN) || mlx_is_key_down(xlib, MLX_KEY_S))
		translate(edges, 0, 1);
	if (mlx_is_key_down(xlib, MLX_KEY_LEFT) || mlx_is_key_down(xlib, MLX_KEY_A))
		translate(edges, -1, 0);
	if (mlx_is_key_down(xlib, MLX_KEY_RIGHT) || mlx_is_key_down(xlib,
			MLX_KEY_D))
		translate(edges, 1, 0);
	if ((mlx_is_key_down(xlib, MLX_KEY_LEFT) || mlx_is_key_down(xlib,
				MLX_KEY_A)) && mlx_is_key_down(xlib, MLX_KEY_LEFT_SHIFT))
		rotate(scene, 1.0);
	if ((mlx_is_key_down(xlib, MLX_KEY_RIGHT) || mlx_is_key_down(xlib,
				MLX_KEY_D)) && mlx_is_key_down(xlib, MLX_KEY_LEFT_SHIFT))
		rotate(scene, -1.0);
}

void	render_frame(t_scene *scene)
{
	mlx_image_t	*image;

	image = (*scene).image;
	ft_bzero((*image).pixels, (*image).width * (*image).height * sizeof(int));
	draw_edges(scene);
	key_hook(scene);
	ft_printf("Rendering frame... Press 'ESC' to exit.\r");
}

void	render_wireframe(t_scene *scene)
{
	(*scene).xlib = mlx_init(WIDTH, HEIGHT, TITLE, 0);
	if (!(*scene).xlib)
		return (clean_halt(scene));
	(*scene).image = mlx_new_image((*scene).xlib, WIDTH, HEIGHT);
	if (!(*scene).image)
		return (clean_halt(scene));
	if (mlx_image_to_window((*scene).xlib, (*scene).image, 0, 0) < 0)
		return (clean_halt(scene));
	mlx_loop_hook((*scene).xlib, (void (*)(void *))render_frame, scene);
	mlx_close_hook((*scene).xlib, (void (*)(void *))mlx_close_window,
		(*scene).xlib);
	mlx_loop((*scene).xlib);
	mlx_terminate((*scene).xlib);
}
