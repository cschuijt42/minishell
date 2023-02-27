/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/09 21:07:47 by cschuijt      #+#    #+#                 */
/*   Updated: 2022/10/17 16:55:35 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <limits.h>

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*pnt;
	size_t	totalsize;
	size_t	maxsize;

	maxsize = -1;
	totalsize = 0;
	if (size == 0 || nmemb == 0)
		pnt = malloc(0);
	else
	{
		if ((maxsize / size) < nmemb)
			return (NULL);
		totalsize = nmemb * size;
		pnt = malloc(totalsize);
	}
	if (!pnt)
		return (NULL);
	ft_bzero(pnt, totalsize);
	return (pnt);
}
