/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 13:46:25 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/05/03 13:46:27 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*array;

	i = 0;
	array = (unsigned char *)malloc(size * count);
	if (!array)
		return (NULL);
	while (i < count * size)
	{
		array[i] = 0;
		i++;
	}
	return (array);
}
