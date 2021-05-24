/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digits_in_number.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 15:50:18 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/05/29 15:50:26 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			ft_digits_in_number(int num)
{
	int	count;

	if (num == -2147483648)
		return (11);
	count = (num < 0);
	num = num * ((num < 0) ? -1 : 1);
	while (num / 10 != 0)
	{
		count++;
		num /= 10;
	}
	return (count + 1);
}
