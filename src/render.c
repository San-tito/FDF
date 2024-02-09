/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:10:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/09 19:29:56 by sguzman          ###   ########.fr       */
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

void	render_frame(void *param)
{
	t_scene		*scene;
	mlx_image_t	*image;

	scene = (t_scene *)param;
	image = (*scene).image;
	ft_bzero((*image).pixels, (*image).width * (*image).height * sizeof(int));
	draw_edges(param);
	ft_printf("Rendering \r");
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_scene	*scene;
	t_list	*edges;

	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE
		&& keydata.modifier == MLX_CONTROL)
		puts("Gotta grab it all!");
	scene = (t_scene *)param;
	edges = (*scene).edges;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window((*scene).xlib);
	if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
		translate(edges, 0, -1);
	if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
		translate(edges, 0, 1);
	if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
		translate(edges, -1, 0);
	if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
		translate(edges, 1, 0);
	if (keydata.key == MLX_KEY_EQUAL)
		zoom(scene, 1);
	if (keydata.key == MLX_KEY_MINUS)
		zoom(scene, -1);
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
	mlx_key_hook((*scene).xlib, key_hook, scene);
	mlx_loop_hook((*scene).xlib, render_frame, scene);
	mlx_loop((*scene).xlib);
	mlx_terminate((*scene).xlib);
}
