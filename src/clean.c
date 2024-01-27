/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 00:46:40 by sguzman           #+#    #+#             */
/*   Updated: 2024/01/27 20:56:32 by sguzman          ###   ########.fr       */
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

void	mlxclear(t_mlx *mlx)
{
	if ((*mlx).img_ptr)
		mlx_destroy_image((*mlx).mlx_ptr, (*mlx).img_ptr);
	if ((*mlx).win_ptr)
		mlx_destroy_window((*mlx).mlx_ptr, (*mlx).win_ptr);
	if ((*mlx).mlx_ptr)
	{
		mlx_destroy_display((*mlx).mlx_ptr);
		free((*mlx).mlx_ptr);
	}
}
