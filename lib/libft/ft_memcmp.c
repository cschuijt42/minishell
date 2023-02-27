/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/09 16:34:37 by cschuijt      #+#    #+#                 */
/*   Updated: 2022/10/13 14:22:20 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n > 0)
	{
		if (*((char *) s1) != *((char *) s2))
			return (*((unsigned char *) s1) - *((unsigned char *) s2));
		s1++;
		s2++;
		n--;
	}
	return (0);
}
