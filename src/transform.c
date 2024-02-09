/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 08:28:33 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/09 19:19:56 by sguzman          ###   ########.fr       */
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
		(*edge).x += tx;
		(*edge).y += ty;
		current = (*current).next;
	}
}

void	zoom(t_scene *scene, int factor)
{
	(*scene).scale += factor;
}
