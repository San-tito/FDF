/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:10:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/01/27 02:28:58 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	render_wireframe(t_list **edges)
{
	void	*mlx;

	(void)edges;
	mlx = mlx_init();
	mlx_new_window(mlx,640 , 480, "FDF!");
	mlx_loop(mlx);
}
