/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:31:35 by sguzman           #+#    #+#             */
/*   Updated: 2024/01/23 19:01:07 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	extract_line(char *line, t_list **edges, int ordinate)
{
	int		axis;
	t_edge	edge;
	t_list	*new;
	char	**coordinates;

	coordinates = ft_split(line, ' ');
	if (!coordinates)
		return ;
	axis = 0;
	while (*(coordinates + axis))
	{
		edge.x = axis;
		edge.y = ordinate;
		edge.z = ft_atoi(*(coordinates + axis++));
		edge.color = 0;
		new = ft_lstnew(&edge);
		ft_lstadd_back(edges, new);
	}
}

void	read_edges(char *pathname, t_list **edges)
{
	int		ordinate;
	int		fd;
	char	*line;

	fd = open(pathname, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	ordinate = 0;
	line = get_next_line(fd);
	while (line)
	{
		extract_line(line, edges, ordinate++);
		free(line);
		line = get_next_line(fd);
	}
}

int	main(int argc, char **argv)
{
	t_list	*edges;

	edges = NULL;
	if (argc != 2)
		return (EXIT_FAILURE);
	read_edges(*(argv + 1), &edges);
	return (EXIT_SUCCESS);
}
