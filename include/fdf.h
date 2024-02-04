/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:31:26 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/01 12:23:03 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#ifdef __linux__
#include "../libs/minilibx_Linux/mlx.h"
#endif
#ifdef __APPLE__
#include "../libs/minilibx_Darwin/mlx.h"
#endif

# include "../libs/libftprintf/include/ft_printf.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>

# define TITLE " Wireframe Model "
# define WIDTH 1280
# define HEIGHT 720

/* ************************************************************************** */
/*                           Definition of the Xlib Structure                 */
/* ************************************************************************** */
typedef struct s_xlib
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*img_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_xlib;

/* ************************************************************************** */
/*                           Definition of the Scene Structure                */
/* ************************************************************************** */
typedef struct s_scene
{
	t_xlib			xlib;
	t_list			*edges;
	unsigned int	scale;
}					t_scene;

/* ************************************************************************** */
/*                           Definition of the Edge Structure                 */
/* ************************************************************************** */
typedef struct s_edge
{
	int				x;
	int				y;
	int				z;
	unsigned int	color;
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
void				*translate(int dx, int dy);
void				center(t_list **edges, int width, int height);

/* ************************************************************************** */
/*                             Memory Freers                                  */
/* ************************************************************************** */
void				lstclear(t_list **lst);
void				arrclear(char **arr);
void				xlibclear(t_xlib *xlib);

#endif
