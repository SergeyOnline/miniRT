/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 19:10:16 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/11 19:10:18 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	calculate_divider(char **tmp, int *divider)
{
	int i;
	int nb;

	i = 0;
	while (tmp[1][i++] == '0')
		*divider *= 10;
	nb = ft_atoi(tmp[1]);
	while ((ft_digits_in_number(nb)) > 1)
	{
		*divider *= 10;
		nb /= 10;
	}
	*divider *= 10;
}

float		ft_atof(const char *str)
{
	float			result;
	int				divider;
	char			**tmp;
	int				nb;

	divider = 1;
	result = (float)ft_atoi(str);
	tmp = ft_split(str, '.');
	if (tmp != NULL && tmp[1] != NULL)
	{
		calculate_divider(tmp, &divider);
		nb = ft_atoi(tmp[1]);
		if (result < 0 || (result == 0 && str[0] == '-'))
			result -= (float)nb / (float)divider;
		else
			result += (float)nb / (float)divider;
	}
	clear_two_dim_arr(tmp);
	return (result);
}
