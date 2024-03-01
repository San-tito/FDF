/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:10:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/01 15:35:36 by sguzman          ###   ########.fr       */
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

void	render_frame(t_scene *scene)
{
	mlx_image_t	*image;

	handle_input(scene);
	if ((*scene).refresh)
	{
		image = (*scene).image;
		ft_bzero((*image).pixels, (*image).width * (*image).height
			* sizeof(int));
		draw_edges(scene);
		(*scene).refresh = 0;
	}
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
