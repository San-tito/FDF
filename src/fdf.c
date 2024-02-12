/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:31:35 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/12 16:07:41 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_scene	scene;

	scene = (t_scene){};
	scene.scale = 4;
	if (argc != 2)
		return (EXIT_SUCCESS);
	parse_map(*(argv + 1), &scene.edges);
	render_wireframe(&scene);
	lstclear(&scene.edges);
	return (EXIT_SUCCESS);
}
