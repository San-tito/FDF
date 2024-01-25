/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:11:24 by sguzman           #+#    #+#             */
/*   Updated: 2024/01/25 18:52:35 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	parse_color(char *token)
{
	int			color;
	const char	*start = ft_strchr(token, ',');

	color = 0x000000;
	if (!start)
		return (0xFFFFFF);
	token = (char *)start + 1;
	if (*token == '0' && (*(token + 1) == 'x' || *(token + 1) == 'X'))
		token += 2;
	while (ft_isdigit(*token) || (*token >= 'a' && *token <= 'f')
		|| (*token >= 'A' && *token <= 'F'))
	{
		color *= 16;
		if (ft_isdigit(*token))
			color += (*token - '0');
		else if (*token >= 'a' && *token <= 'f')
			color += (*token - 'a' + 10);
		else if (*token >= 'A' && *token <= 'F')
			color += (*token - 'A' + 10);
		token++;
	}
	return (color);
}

static t_edge	parse_coordinate(int axis, int ordinate, char *token)
{
	t_edge	edge;

	edge.x = axis;
	edge.y = ordinate;
	edge.z = ft_atoi(token);
	edge.color = parse_color(token);
	ft_printf("z -> %i; color -> %i\n", edge.z, edge.color);
	return (edge);
}

static void	parse_line(char *line, t_list **edges, int ordinate, int fd)
{
	t_edge	edge;
	t_list	*new;
	char	**coordinates;
	int		axis;

	coordinates = ft_split(line, ' ');
	if (!coordinates)
	{
		close(fd);
		ft_lstclear(edges, free);
		exit(EXIT_FAILURE);
	}
	axis = 0;
	while (*(coordinates + axis))
	{
		edge = parse_coordinate(axis, ordinate, *(coordinates + axis));
		new = ft_lstnew(&edge);
		if (!new)
		{
			close(fd);
			ft_lstclear(edges, free);
			exit(EXIT_FAILURE);
		}
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
		parse_line(line, edges, ordinate++, fd);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
