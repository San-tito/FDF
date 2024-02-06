/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:10:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/06 19:38:58 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clean_halt(t_scene *scene)
{
	lstclear(&(*scene).edges);
	perror("Error");
	exit(EXIT_FAILURE);
}

int	render_frame(t_scene *scene)
{
	(void)scene;
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
	//if (keycode == 65307)
	//	return (mlx_loop_end((*scene).xlib.mlx_ptr));
	render_frame(scene);
	return (0);
}

void	render_wireframe(t_scene *scene)
{
	t_xlib	*xlib;

	xlib = &(*scene).xlib;
	(*xlib).mlx_ptr = mlx_init(WIDTH, HEIGHT, TITLE, true);
	(*xlib).img_ptr = mlx_new_image((*xlib).mlx_ptr, 256, 256);	

	mlx_put_pixel((*xlib).img_ptr, 0, 0, 0xFF0000FF);
	mlx_loop((*xlib).mlx_ptr);
	mlx_terminate((*xlib).mlx_ptr);

}
