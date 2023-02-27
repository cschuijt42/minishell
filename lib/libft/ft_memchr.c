/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/09 15:43:57 by cschuijt      #+#    #+#                 */
/*   Updated: 2022/10/17 17:19:31 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n > 0)
	{
		if (*((unsigned char *) s) == (unsigned char) c)
			return ((void *) s);
		s++;
		n--;
	}
	return (NULL);
}
