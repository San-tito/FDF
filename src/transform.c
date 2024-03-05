/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 08:28:33 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/05 09:39:37 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate(t_scene *scene, int tx, int ty)
{
	(*scene).translation.i += tx;
	(*scene).translation.j += ty;
	(*scene).refresh = 1;
}

void	zoom(t_scene *scene, int factor)
{
	(*scene).scale += factor;
	(*scene).refresh = 1;
}

void	rotate(t_scene *scene, float rx, float ry)
{
	(*scene).rotation.i += rx;
	(*scene).rotation.j += ry;
	(*scene).refresh = 1;
}

void	dizzy(t_scene *scene, float angle)
{
	(*scene).angle += angle;
	(*scene).refresh = 1;
}
