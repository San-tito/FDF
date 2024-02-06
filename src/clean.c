/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 00:46:40 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/06 19:27:04 by sguzman          ###   ########.fr       */
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

