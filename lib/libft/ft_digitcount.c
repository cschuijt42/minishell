/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_digitcount.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/27 17:07:56 by cschuijt      #+#    #+#                 */
/*   Updated: 2022/12/27 17:07:56 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_digitcount(size_t num)
{
	size_t	digits;

	digits = 1;
	num /= 10;
	while (num)
	{
		digits++;
		num /= 10;
	}
	return (digits);
}
