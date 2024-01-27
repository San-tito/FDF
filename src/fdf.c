/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:31:35 by sguzman           #+#    #+#             */
/*   Updated: 2024/01/27 21:09:15 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_list(t_list *head)
{
	t_list	*current;
	t_edge	*edge;
	t_edge	*next;

	current = head;
	while (current)
	{
		edge = (t_edge *)(*current).content;
		ft_printf("%d,%d ", edge->z, edge->color);
		current = current->next;
		if (current != NULL)
		{
			next = (t_edge *)current->content;
			if (next->y > edge->y)
				ft_printf("\n");
		}
	}
}

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
