/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:01:06 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/23 19:07:41 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	handle_zoom(mlx_t *xlib, t_scene *scene)
{
	if (mlx_is_key_down(xlib, MLX_KEY_EQUAL))
		zoom(scene, 1);
	if (mlx_is_key_down(xlib, MLX_KEY_MINUS))
		zoom(scene, -1);
}

static void	handle_translation(mlx_t *xlib, t_scene *scene)
{
	if (mlx_is_key_down(xlib, MLX_KEY_UP) || mlx_is_key_down(xlib, MLX_KEY_W))
		translate(scene, 0, -1);
	if (mlx_is_key_down(xlib, MLX_KEY_DOWN) || mlx_is_key_down(xlib, MLX_KEY_S))
		translate(scene, 0, 1);
	if (mlx_is_key_down(xlib, MLX_KEY_LEFT) || mlx_is_key_down(xlib, MLX_KEY_A))
		translate(scene, -1, 0);
	if (mlx_is_key_down(xlib, MLX_KEY_RIGHT) || mlx_is_key_down(xlib,
			MLX_KEY_D))
		translate(scene, 1, 0);
}

static void	handle_rotation(mlx_t *xlib, t_scene *scene)
{
	if ((mlx_is_key_down(xlib, MLX_KEY_LEFT) || mlx_is_key_down(xlib,
				MLX_KEY_A)) && mlx_is_key_down(xlib, MLX_KEY_LEFT_SHIFT))
		rotate(scene, 0.1);
	if ((mlx_is_key_down(xlib, MLX_KEY_RIGHT) || mlx_is_key_down(xlib,
				MLX_KEY_D)) && mlx_is_key_down(xlib, MLX_KEY_LEFT_SHIFT))
		rotate(scene, -0.1);
}

void	handle_input(t_scene *scene)
{
	mlx_t	*xlib;

	xlib = (*scene).xlib;
	handle_zoom(xlib, scene);
	handle_translation(xlib, scene);
	handle_rotation(xlib, scene);
	if (mlx_is_key_down(xlib, MLX_KEY_ESCAPE))
		mlx_close_window(xlib);
}
