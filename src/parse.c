/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:11:24 by sguzman           #+#    #+#             */
/*   Updated: 2024/01/25 12:10:23 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	is_valid_hex_digit(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A'
			&& c <= 'F'));
}

static int	get_hex_digit_value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

static int	parse_color(char *token)
{
	int		color;
	char	*start;

	start = ft_strchr(token, ',');
	color = 0x000000;
	if (!start)
		return (0xFFFFFF);
	else
		token = ++start;
	if (*token == '0' && (*(token + 1) == 'x' || *(token + 1) == 'X'))
		token += 2;
	while (is_valid_hex_digit(*token))
	{
		color = color * 16 + get_hex_digit_value(*token);
		token++;
	}
	return (color);
}

static void	parse_coordinate(t_edge *edge, int axis, int ordinate, char *token)
{
	(*edge).x = axis;
	(*edge).y = ordinate;
	(*edge).z = ft_atoi(token);
	(*edge).color = parse_color(token);
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
		parse_coordinate(&edge, axis, ordinate, *(coordinates + axis));
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
