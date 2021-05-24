/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:55:27 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/08/27 14:55:31 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light_ring	*new_light_ring(t_light light)
{
	t_light_ring *light_ring;

	if ((light_ring = (t_light_ring *)malloc(sizeof(*light_ring))))
	{
		light_ring->light = light;
		light_ring->next = light_ring;
		light_ring->prev = light_ring;
		light_ring->size = 1;
	}
	else
		return (NULL);
	return (light_ring);
}

void			add_element_light_ring(t_light_ring **ring, t_light light)
{
	t_light_ring	*ptr;
	t_light_ring	*element;
	t_light_ring	*tmp;

	ptr = *ring;
	if (ptr)
	{
		element = new_light_ring(light);
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
		*ring = new_light_ring(light);
}

void			remove_element_light_ring(t_light_ring **ring)
{
	t_light_ring	*ptr;

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

void			clear_light_ring(t_light_ring **ring)
{
	while (*ring)
		remove_element_light_ring(ring);
}
