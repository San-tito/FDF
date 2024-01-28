/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 00:46:40 by sguzman           #+#    #+#             */
/*   Updated: 2024/01/28 22:22:33 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	lstclear(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = (**lst).next;
		free((**lst).content);
		free(*lst);
		*lst = tmp;
	}
}

void	arrclear(char **arr)
{
	int	i;

	i = 0;
	while (*(arr + i))
		free(*(arr + i++));
	free(arr);
}

void	xlibclear(t_xlib *xlib)
{
	if ((*xlib).img_ptr)
		mlx_destroy_image((*xlib).mlx_ptr, (*xlib).img_ptr);
	if ((*xlib).win_ptr)
		mlx_destroy_window((*xlib).mlx_ptr, (*xlib).win_ptr);
	if ((*xlib).mlx_ptr)
	{
		mlx_destroy_display((*xlib).mlx_ptr);
		free((*xlib).mlx_ptr);
	}
}
