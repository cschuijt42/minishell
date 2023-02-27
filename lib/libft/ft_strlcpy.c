/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 14:29:58 by cschuijt      #+#    #+#                 */
/*   Updated: 2022/10/12 17:21:57 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *s);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	n;
	size_t	len;
	size_t	size;

	if (dstsize > 0)
		size = dstsize - 1;
	else
		size = 0;
	len = ft_strlen(src);
	n = 0;
	while (*src && n < size)
	{
		*dst = *src;
		dst++;
		src++;
		n++;
	}
	if (dstsize > 0)
		*dst = '\0';
	return (len);
}
