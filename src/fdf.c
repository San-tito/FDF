/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:31:35 by sguzman           #+#    #+#             */
/*   Updated: 2024/01/22 13:25:35 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	read_points(char *pathname, t_list **points)
{
	int		fd;
	char	*line;

	fd = open(pathname, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	line = get_next_line(fd);
	while (line)
	{
		ft_printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
}

int	main(int argc, char **argv)
{
	t_list	*points;

	points = NULL;
	if (argc != 2)
		return (EXIT_FAILURE);
	read_points(*(argv + 1), &points);
	return (EXIT_SUCCESS);
}
