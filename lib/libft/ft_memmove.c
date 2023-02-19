/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/09 17:59:15 by cschuijt      #+#    #+#                 */
/*   Updated: 2022/10/17 12:12:53 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static void	move_rtl(void *dest, const void *src, size_t n)
{
	dest = (char *) dest + n - 1;
	src = (char *) src + n - 1;
	while (n > 0)
	{
		*((char *) dest) = *((char *) src);
		dest--;
		src--;
		n--;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*pnt;

	pnt = dest;
	if (!dest && !src)
		return (pnt);
	if (src < dest)
		move_rtl(dest, src, n);
	else
	{
		while (n > 0)
		{
			*((char *) dest) = *((char *) src);
			dest++;
			src++;
			n--;
		}
	}
	return (pnt);
}
