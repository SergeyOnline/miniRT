/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_cy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 22:21:56 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/18 22:21:58 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cy_ring		*new_cy_ring(t_cylinder cy)
{
	t_cy_ring *cy_ring;

	if ((cy_ring = (t_cy_ring *)malloc(sizeof(*cy_ring))))
	{
		cy_ring->cy = cy;
		cy_ring->next = cy_ring;
		cy_ring->prev = cy_ring;
		cy_ring->size = 1;
	}
	else
		return (NULL);
	return (cy_ring);
}

void			add_element_cy_ring(t_cy_ring **ring, t_cylinder cy)
{
	t_cy_ring	*ptr;
	t_cy_ring	*element;
	t_cy_ring	*tmp;

	ptr = *ring;
	if (ptr)
	{
		element = new_cy_ring(cy);
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
		*ring = new_cy_ring(cy);
}

void			remove_element_cy_ring(t_cy_ring **ring)
{
	t_cy_ring	*ptr;

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

void			clear_cy_ring(t_cy_ring **ring)
{
	while (*ring)
		remove_element_cy_ring(ring);
}
