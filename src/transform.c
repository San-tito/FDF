/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 08:28:33 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/19 20:11:31 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate(t_scene *scene, int tx, int ty)
{
	scene->translate[0] += tx;
	scene->translate[1] += ty;
}

void	zoom(t_scene *scene, int factor)
{
	(*scene).scale += factor;
}

void	rotate(t_scene *scene, float angle)
{
	(*scene).angle += angle;
}
