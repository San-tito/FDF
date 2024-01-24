/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:11:24 by sguzman           #+#    #+#             */
/*   Updated: 2024/01/24 19:59:01 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_edge	parse_coordinate(int axis, int ordinate, char *token)
{
	t_edge	edge;

	edge.x = axis;
	edge.y = ordinate;
	edge.z = ft_atoi(token);
	edge.color = 0xFFFFFF;
	// if (ft_strchr(token, ','))
	return (edge);
}

void	parse_line(char *line, t_list **edges, int ordinate)
{
	t_edge	edge;
	t_list	*new;
	char	**coordinates;
	int		axis;

	coordinates = ft_split(line, ' ');
	if (!coordinates)
		return ;
	axis = 0;
	while (*(coordinates + axis))
	{
		edge = parse_coordinate(axis, ordinate, *(coordinates + axis));
		new = ft_lstnew(&edge);
		ft_lstadd_back(edges, new);
		axis++;
	}
}

void	parse_map(char *pathname, t_list **edges)
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
		parse_line(line, edges, ordinate++);
		free(line);
		line = get_next_line(fd);
	}
}
