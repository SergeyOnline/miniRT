/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 18:58:08 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/04/30 18:58:13 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int			i;
	long int	result;
	int			is_negative;
	int			count;

	count = 0;
	i = 0;
	result = 0;
	is_negative = 0;
	while (str && ((str[i] == ' ') || (str[i] == '\n') || (str[i] == '\t')
		|| (str[i] == '\f') || (str[i] == '\v') || (str[i] == '\r')))
		i++;
	if (str && (str[i] == '+' || str[i] == '-'))
		is_negative = (str[i++] == '-');
	while (str && str[i] >= '0' && str[i] <= '9')
	{
		count++;
		if (count > 20)
			return ((result > 0) * (-1) + is_negative);
		result = result * 10 + (str[i++] - '0');
	}
	if (is_negative)
		result *= (-1);
	return ((int)result);
}
