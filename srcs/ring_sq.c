/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_sq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 22:00:29 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/18 22:00:31 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sq_ring		*new_sq_ring(t_square sq)
{
	t_sq_ring *sq_ring;

	if ((sq_ring = (t_sq_ring *)malloc(sizeof(*sq_ring))))
	{
		sq_ring->sq = sq;
		sq_ring->next = sq_ring;
		sq_ring->prev = sq_ring;
		sq_ring->size = 1;
	}
	else
		return (NULL);
	return (sq_ring);
}

void			add_element_sq_ring(t_sq_ring **ring, t_square sq)
{
	t_sq_ring	*ptr;
	t_sq_ring	*element;
	t_sq_ring	*tmp;

	ptr = *ring;
	if (ptr)
	{
		element = new_sq_ring(sq);
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
		*ring = new_sq_ring(sq);
}

void			remove_element_sq_ring(t_sq_ring **ring)
{
	t_sq_ring	*ptr;

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

void			clear_sq_ring(t_sq_ring **ring)
{
	while (*ring)
		remove_element_sq_ring(ring);
}
