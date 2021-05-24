/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 23:29:22 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/04/29 23:29:27 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (0);
}

void		ft_putstr(char *s)
{
	int	index;

	index = 0;
	if (s != NULL)
	{
		while (s[index] != '\0')
		{
			ft_putchar(s[index]);
			index++;
		}
	}
}
