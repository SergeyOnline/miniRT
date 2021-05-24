/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_pl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:34:05 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/18 21:34:08 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pl_ring		*new_pl_ring(t_plane pl)
{
	t_pl_ring *pl_ring;

	if ((pl_ring = (t_pl_ring *)malloc(sizeof(*pl_ring))))
	{
		pl_ring->pl = pl;
		pl_ring->next = pl_ring;
		pl_ring->prev = pl_ring;
		pl_ring->size = 1;
	}
	else
		return (NULL);
	return (pl_ring);
}

void			add_element_pl_ring(t_pl_ring **ring, t_plane pl)
{
	t_pl_ring	*ptr;
	t_pl_ring	*element;
	t_pl_ring	*tmp;

	ptr = *ring;
	if (ptr)
	{
		element = new_pl_ring(pl);
		element->size = (*ring)->size + 1;
		(*ring)->next = element;
		element->prev = *ring;
		tmp = *ring;
		while (tmp->size != 1)
			tmp = tmp->prev;
		tmp->prev = element;
		element->next = tmp;
		*ring = element;
	}
	else
		*ring = new_pl_ring(pl);
}

void			remove_element_pl_ring(t_pl_ring **ring)
{
	t_pl_ring	*ptr;

	ptr = *ring;
	if (ptr && ptr->next != ptr)
	{
		(ptr->prev)->next = ptr->next;
		(ptr->next)->prev = ptr->prev;
		*ring = ptr->next;
		(*ring)->size = ptr->size;
		ptr->next = NULL;
		ptr->prev = NULL;
		free(ptr);
		ptr = (*ring)->next;
		while ((ptr->size)-- != 1)
			ptr = ptr->next;
	}
	else if (ptr && ptr->next == ptr)
	{
		(*ring)->next = NULL;
		(*ring)->prev = NULL;
		*ring = NULL;
		free(ptr);
	}
}

void			clear_pl_ring(t_pl_ring **ring)
{
	while (*ring)
		remove_element_pl_ring(ring);
}
