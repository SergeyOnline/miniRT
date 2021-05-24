/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 13:37:17 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/10 13:37:20 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ft_strdup(const char *s1)
{
	int		count;
	char	*str;

	count = 0;
	while (s1[count])
		count++;
	str = (char *)malloc(sizeof(*str) * count + 1);
	if (str == NULL)
		return (NULL);
	count = 0;
	while (s1[count] != '\0')
	{
		str[count] = s1[count];
		count++;
	}
	str[count] = '\0';
	return (str);
}
