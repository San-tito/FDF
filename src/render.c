/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:10:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/01/27 16:31:44 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_win(int keycode, t_mlx *mlx)
{
	(void)keycode;
	mlx_destroy_window((*mlx).mlx_ptr, (*mlx).win_ptr);
	return (mlx_loop_end((*mlx).mlx_ptr));
}

void	render_wireframe(t_list **edges)
{
	t_mlx	mlx;

	(void)edges;
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT,
			"FDF!");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx.img_addr = mlx_get_data_addr(mlx.img_ptr, &mlx.bits_per_pixel,
			&mlx.size_line, &mlx.endian);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img_ptr, (SCREEN_WIDTH
			- SCREEN_WIDTH) / 2, (SCREEN_HEIGHT - SCREEN_HEIGHT) / 2);
	mlx_hook(mlx.win_ptr, 2, 1L << 0, close_win, &mlx);
	mlx_loop(mlx.mlx_ptr);
}
