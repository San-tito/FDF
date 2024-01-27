/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:31:26 by sguzman           #+#    #+#             */
/*   Updated: 2024/01/27 16:13:06 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libs/libftprintf/include/ft_printf.h"
# include "../libs/minilibx/mlx.h"
# include <fcntl.h>

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720

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
/*                           Rendering Function                               */
/* ************************************************************************** */
void				render_wireframe(t_list **edges);

/* ************************************************************************** */
/*                              MLX Structure                                 */
/* ************************************************************************** */
typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*img_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_mlx;

/* ************************************************************************** */
/*                             Memory Freers                                  */
/* ************************************************************************** */
void				lstclear(t_list **lst);
void				arrclear(char **arr);

#endif
