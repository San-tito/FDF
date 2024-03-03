/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:31:35 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/03 13:47:29 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	initialize_scene(t_scene *scene)
{
	(*scene).refresh = 1;
	(*scene).scale = 10;
	(*scene).angle = M_PI / 6;
	translate(scene, (WIDTH / 2), (HEIGHT / 2));
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	scene = (t_scene){};
	if (argc != 2)
		return (EXIT_SUCCESS);
	parse_map(*(argv + 1), &scene.edges);
	initialize_scene(&scene);
	render_wireframe(&scene);
	lstclear(&scene.edges);
	return (EXIT_SUCCESS);
}
