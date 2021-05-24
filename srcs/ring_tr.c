/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_tr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 22:51:46 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/18 22:51:48 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tr_ring		*new_tr_ring(t_triangle tr)
{
	t_tr_ring *tr_ring;

	if ((tr_ring = (t_tr_ring *)malloc(sizeof(*tr_ring))))
	{
		tr_ring->tr = tr;
		tr_ring->next = tr_ring;
		tr_ring->prev = tr_ring;
		tr_ring->size = 1;
	}
	else
		return (NULL);
	return (tr_ring);
}

void			add_element_tr_ring(t_tr_ring **ring, t_triangle tr)
{
	t_tr_ring	*ptr;
	t_tr_ring	*element;
	t_tr_ring	*tmp;

	ptr = *ring;
	if (ptr)
	{
		element = new_tr_ring(tr);
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
		*ring = new_tr_ring(tr);
}

void			remove_element_tr_ring(t_tr_ring **ring)
{
	t_tr_ring	*ptr;

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

void			clear_tr_ring(t_tr_ring **ring)
{
	while (*ring)
		remove_element_tr_ring(ring);
}
