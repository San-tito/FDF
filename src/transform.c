/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 08:28:33 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/12 16:38:25 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate(t_list *lst, int tx, int ty)
{
	t_list	*current;
	t_edge	*edge;

	current = lst;
	while (current)
	{
		edge = (*current).content;
		(*edge).axis += tx;
		(*edge).ordinate += ty;
		current = (*current).next;
	}
}

void	zoom(t_scene *scene, int factor)
{
	(*scene).scale += factor;
}
