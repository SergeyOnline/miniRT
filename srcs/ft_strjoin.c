/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 13:39:31 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/10 13:39:55 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		i;
	int		index;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	index = 0;
	i = 0;
	len = 0;
	while (s1[i++])
		len++;
	i = 0;
	while (s2[i++])
		len++;
	if (!(str = (char *)malloc(sizeof(*str) * len + 1)))
		return (NULL);
	i = 0;
	while (s1[i])
		str[index++] = s1[i++];
	i = 0;
	while (s2[i])
		str[index++] = s2[i++];
	str[index] = '\0';
	return (str);
}
