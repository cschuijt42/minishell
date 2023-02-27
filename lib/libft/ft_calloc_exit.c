/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc_exit.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/04 14:35:42 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/01/04 14:35:42 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>

void	ft_bzero(void *s, size_t n);

void	*ft_calloc_exit(size_t nmemb, size_t size)
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
			exit_perror("malloc error");
		totalsize = nmemb * size;
		pnt = malloc(totalsize);
	}
	if (!pnt)
		exit_perror("malloc error");
	ft_bzero(pnt, totalsize);
	return (pnt);
}
