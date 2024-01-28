/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:31:26 by sguzman           #+#    #+#             */
/*   Updated: 2024/01/28 22:54:02 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libs/libftprintf/include/ft_printf.h"
# include "../libs/minilibx/mlx.h"
# include <fcntl.h>
# include <math.h>

# define TITLE "🚀 Wireframe Model 🌐"
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
	float			scale;
}					t_scene;

/* ************************************************************************** */
/*                           Definition of the Edge Structure                 */
/* ************************************************************************** */
typedef struct s_edge
{
	float			x;
	float			y;
	float			z;
	unsigned int	color;
}					t_edge;

/* ************************************************************************** */
/*                            Parsing Helpers                                 */
/* ************************************************************************** */
char				*get_next_line(int fd);
void				parse_map(char *pathname, t_list **edges);

/* ************************************************************************** */
/*                           Rendering Function                               */
/* ************************************************************************** */
void				render_wireframe(t_scene *scene);

/* ************************************************************************** */
/*                             Memory Freers                                  */
/* ************************************************************************** */
void				lstclear(t_list **lst);
void				arrclear(char **arr);
void				xlibclear(t_xlib *xlib);

#endif
