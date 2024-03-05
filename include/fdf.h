/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:31:26 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/05 09:39:50 by sguzman          ###   ########.fr       */
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
# define ISOMETRIC 1
# define CABINET 0

/* ************************************************************************** */
/*                        Definition of the Vector Structure                 */
/* ************************************************************************** */
typedef struct s_vector
{
	int			i;
	int			j;
}				t_vector;

/* ************************************************************************** */
/*                        Definition of the Transform Structure               */
/* ************************************************************************** */
typedef struct t_transform
{
	float		i;
	float		j;
}				t_transform;

/* ************************************************************************** */
/*                           Definition of the Scene Structure                */
/* ************************************************************************** */
typedef struct s_scene
{
	char refresh : 1;
	char view : 1;
	mlx_t		*xlib;
	mlx_image_t	*image;
	t_list		*edges;
	float		angle;
	int			scale;
	t_transform	rotation;
	t_vector	translation;
}				t_scene;

/* ************************************************************************** */
/*                           Definition of the Edge Structure                 */
/* ************************************************************************** */
typedef struct s_edge
{
	double		axis;
	double		ordinate;
	double		altitude;
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
void			draw_line(mlx_image_t *image, t_vector v0, t_vector v1,
					int color);
void			render_wireframe(t_scene *scene);

/* ************************************************************************** */
/*                                Transform                                   */
/* ************************************************************************** */
void			translate(t_scene *scene, int dx, int dy);
void			rotate(t_scene *scene, float dx, float dy);
void			dizzy(t_scene *scene, float angle);
void			zoom(t_scene *scene, int factor);

/* ************************************************************************** */
/*                                 Input                                      */
/* ************************************************************************** */
void			handle_input(t_scene *scene);

/* ************************************************************************** */
/*                             Memory Freers                                  */
/* ************************************************************************** */
void			lstclear(t_list **lst);
void			arrclear(char **arr);

#endif
