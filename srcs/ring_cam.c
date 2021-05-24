/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:01:54 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/13 16:01:57 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cam_ring		*new_cam_ring(t_camera cam)
{
	t_cam_ring *cam_ring;

	if ((cam_ring = (t_cam_ring *)malloc(sizeof(*cam_ring))))
	{
		cam_ring->cam = cam;
		cam_ring->next = cam_ring;
		cam_ring->prev = cam_ring;
		cam_ring->size = 1;
	}
	else
		return (NULL);
	return (cam_ring);
}

void			add_element_cam_ring(t_cam_ring **ring, t_camera cam)
{
	t_cam_ring	*ptr;
	t_cam_ring	*element;
	t_cam_ring	*tmp;

	ptr = *ring;
	if (ptr)
	{
		element = new_cam_ring(cam);
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
		*ring = new_cam_ring(cam);
}

void			remove_element_cam_ring(t_cam_ring **ring)
{
	t_cam_ring	*ptr;

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

void			clear_cam_ring(t_cam_ring **ring)
{
	while (*ring)
		remove_element_cam_ring(ring);
}
