/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 08:28:33 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/01 08:36:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*translate(int tx, int ty)
{
	t_edge	*edge;

	void translate(void *content)
	{
		edge = (t_edge *)content;
		(*edge).x += tx;
		(*edge).y += ty;
	}
	return (translate);
}
