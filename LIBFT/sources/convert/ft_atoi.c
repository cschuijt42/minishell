/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-cloe <mde-cloe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 18:00:40 by mde-cloe          #+#    #+#             */
/*   Updated: 2021/12/13 18:06:56 by mde-cloe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	search_string(char *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		++set;
	}
	return (0);
}

int	ft_atoi(const char	*str)
{
	size_t	i;
	long	result;
	long	isneg;

	i = 0;
	result = 0;
	isneg = 1;
	while (search_string("\t\n\v\f\r ", str[i]) && str[i])
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			isneg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * isneg);
}
