/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 21:37:13 by cschuijt      #+#    #+#                 */
/*   Updated: 2022/10/14 12:23:21 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

void	*ft_calloc(size_t nmemb, size_t size);

static unsigned int	count_digits(int n)
{
	unsigned int	digits;

	digits = 1;
	while (n < -9)
	{
		digits++;
		n = n / 10;
	}
	return (digits);
}

static void	write_number(int n, char *dst)
{
	*dst = 48 - (n % 10);
	n = n / 10;
	if (n < 0)
		write_number(n, dst - 1);
}

char	*ft_itoa(int n)
{
	unsigned int	chars;
	char			*str;
	int				negative;

	negative = false;
	chars = 1;
	if (n < 0)
	{
		chars++;
		negative = true;
	}
	else
		n = -n;
	chars = chars + count_digits(n);
	str = ft_calloc(sizeof(char), chars);
	if (!str)
		return (NULL);
	write_number(n, str + chars - 2);
	if (negative == true)
		str[0] = '-';
	return (str);
}
