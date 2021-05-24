/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_sp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 15:01:42 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/18 15:01:45 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sp_ring		*new_sp_ring(t_sphere sp)
{
	t_sp_ring *sp_ring;

	if ((sp_ring = (t_sp_ring *)malloc(sizeof(*sp_ring))))
	{
		sp_ring->sp = sp;
		sp_ring->next = sp_ring;
		sp_ring->prev = sp_ring;
		sp_ring->size = 1;
	}
	else
		return (NULL);
	return (sp_ring);
}

void			add_element_sp_ring(t_sp_ring **ring, t_sphere sp)
{
	t_sp_ring	*ptr;
	t_sp_ring	*element;
	t_sp_ring	*tmp;

	ptr = *ring;
	if (ptr)
	{
		element = new_sp_ring(sp);
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
		*ring = new_sp_ring(sp);
}

void			remove_element_sp_ring(t_sp_ring **ring)
{
	t_sp_ring	*ptr;

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

void			clear_sp_ring(t_sp_ring **ring)
{
	while (*ring)
		remove_element_sp_ring(ring);
}
