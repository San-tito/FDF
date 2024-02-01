/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:10:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/01 12:15:32 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	clean_halt(t_scene *scene)
{
	xlibclear(&(*scene).xlib);
	lstclear(&(*scene).edges);
	perror("Error");
	exit(EXIT_FAILURE);
}

int	render_frame(t_scene *scene)
{
	t_xlib	*xlib;

	xlib = &(*scene).xlib;
	mlx_destroy_image((*xlib).mlx_ptr, (*xlib).img_ptr);
	(*xlib).img_ptr = mlx_new_image((*xlib).mlx_ptr, WIDTH, HEIGHT);
	if (!(*xlib).img_ptr)
		clean_halt(scene);
	(*xlib).img_addr = mlx_get_data_addr((*xlib).img_ptr,
			&(*xlib).bits_per_pixel, &(*xlib).size_line, &(*xlib).endian);
	draw_edges(scene);
	mlx_put_image_to_window((*xlib).mlx_ptr, (*xlib).win_ptr, (*xlib).img_ptr,
		0, 0);
	ft_printf("Rendering \r");
	return (0);
}

int	handle_key(int keycode, t_scene *scene)
{
	if (keycode == 119)
		ft_lstiter((*scene).edges, translate(0, -1));
	else if (keycode == 97)
		ft_lstiter((*scene).edges, translate(-1, 0));
	else if (keycode == 115)
		ft_lstiter((*scene).edges, translate(0, 1));
	else if (keycode == 100)
		ft_lstiter((*scene).edges, translate(1, 0));
	else if (keycode == 61)
		(*scene).scale += 2;
	 else if (keycode == 45)
		(*scene).scale -= 2;
	if (keycode == 65307)
		return (mlx_loop_end((*scene).xlib.mlx_ptr));
	render_frame(scene);
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
	mlx_expose_hook((*xlib).win_ptr, render_frame, scene);
	mlx_key_hook((*xlib).win_ptr, handle_key, scene);
	mlx_loop((*xlib).mlx_ptr);
	ft_printf("Rendering complete!                  \n");
}
