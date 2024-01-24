/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:31:26 by sguzman           #+#    #+#             */
/*   Updated: 2024/01/24 19:50:04 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libs/libftprintf/include/ft_printf.h"
# include "../libs/minilibx/mlx.h"
# include <fcntl.h>

/* ************************************************************************** */
/*                           Definition of the Edge Structure                 */
/* ************************************************************************** */
typedef struct s_edge
{
	int	x;
	int	y;
	int	z;
	int	color;
}		t_edge;

/* ************************************************************************** */
/*                           Parsing Functions                                */
/* ************************************************************************** */
char	*get_next_line(int fd);
t_edge	parse_coordinate(int axis, int ordinate, char *token);
void	parse_line(char *line, t_list **edges, int ordinate);
void	parse_map(char *pathname, t_list **edges);

#endif
