/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:31:26 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/08 02:51:01 by sguzman          ###   ########.fr       */
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
	mlx_t			*xlib;
	mlx_image_t		*image;
	t_list			*edges;
	int	scale;
}					t_scene;

/* ************************************************************************** */
/*                           Definition of the Edge Structure                 */
/* ************************************************************************** */
typedef struct s_edge
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_edge;

/* ************************************************************************** */
/*                            Parsing Helpers                                 */
/* ************************************************************************** */
char				*get_next_line(int fd);
void				parse_map(char *pathname, t_list **edges);

/* ************************************************************************** */
/*                                Rendering                                   */
/* ************************************************************************** */
void				draw_edges(t_scene *scene);
void				render_wireframe(t_scene *scene);

/* ************************************************************************** */
/*                                Transform                                   */
/* ************************************************************************** */
void				translate(t_list *lst, int dx, int dy);
void				scale_factor(t_scene *scene, int factor);

/* ************************************************************************** */
/*                             Memory Freers                                  */
/* ************************************************************************** */
void				lstclear(t_list **lst);
void				arrclear(char **arr);

#endif
