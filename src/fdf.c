/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:31:35 by sguzman           #+#    #+#             */
/*   Updated: 2024/01/27 21:53:24 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_list	*edges;

	mlx = (t_mlx){};
	edges = NULL;
	if (argc != 2)
		return (EXIT_SUCCESS);
	parse_map(*(argv + 1), &edges);
	render_wireframe(&edges, &mlx);
	lstclear(&edges);
	mlxclear(&mlx);
	return (EXIT_SUCCESS);
}
