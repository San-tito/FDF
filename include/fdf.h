/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:31:26 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/12 16:42:02 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/libftprintf/include/ft_printf.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>

# define TITLE "Wireframe Model"
# define WIDTH 1280
# define HEIGHT 960

/* ************************************************************************** */
/*                           Definition of the Scene Structure                */
/* ************************************************************************** */
typedef struct s_scene
{
	mlx_t		*xlib;
	mlx_image_t	*image;
	t_list		*edges;
	size_t		scale;
}				t_scene;

/* ************************************************************************** */
/*                           Definition of the Edge Structure                 */
/* ************************************************************************** */
typedef struct s_edge
{
	size_t		axis;
	size_t		ordinate;
	size_t		altitude;
	size_t		color;
}				t_edge;

/* ************************************************************************** */
/*                           Definition of the Point Structure                */
/* ************************************************************************** */
typedef struct s_point
{
	int			x;
	int			y;
	int			color;
}				t_point;

/* ************************************************************************** */
/*                            Parsing Helpers                                 */
/* ************************************************************************** */
char			*get_next_line(int fd);
void			parse_map(char *pathname, t_list **edges);

/* ************************************************************************** */
/*                                Rendering                                   */
/* ************************************************************************** */
void			draw_edges(t_scene *scene);
void			render_wireframe(t_scene *scene);

/* ************************************************************************** */
/*                                Transform                                   */
/* ************************************************************************** */
void			translate(t_list *lst, int dx, int dy);
void			zoom(t_scene *scene, int factor);

/* ************************************************************************** */
/*                             Memory Freers                                  */
/* ************************************************************************** */
void			lstclear(t_list **lst);
void			arrclear(char **arr);

#endif
