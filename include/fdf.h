/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:31:26 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/23 00:10:16 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "MLX42/MLX42.h"
# include "ft_printf.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define TITLE "Wireframe Model"
# define WIDTH 1280
# define HEIGHT 960

/* ************************************************************************** */
/*                           Definition of the Point Structure                */
/* ************************************************************************** */
typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

/* ************************************************************************** */
/*                           Definition of the Scene Structure                */
/* ************************************************************************** */
typedef struct s_scene
{
	mlx_t		*xlib;
	mlx_image_t	*image;
	t_list		*edges;
	size_t		scale;
	float		angle;
	t_point		translation;
}				t_scene;

/* ************************************************************************** */
/*                           Definition of the Edge Structure                 */
/* ************************************************************************** */
typedef struct s_edge
{
	int			axis;
	int			ordinate;
	int			altitude;
	int			color;
}				t_edge;

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
void			translate(t_scene *scene, int dx, int dy);
void			zoom(t_scene *scene, int factor);
void			rotate(t_scene *scene, float angle);

/* ************************************************************************** */
/*                             Memory Freers                                  */
/* ************************************************************************** */
void			lstclear(t_list **lst);
void			arrclear(char **arr);

#endif
