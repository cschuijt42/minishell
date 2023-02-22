/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 18:00:40 by mde-cloe      #+#    #+#                 */
/*   Updated: 2022/10/11 19:11:49 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void	*dest, const void	*src, size_t	n)
{
	size_t		i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

//even though I thought at first this would cause overflow whenever the size would be bigger than what an unsigned char contains, it actually doesn't matter because we cast the whole pointer to an unsigned char pointer and therefore we only change the bits that belong to that part of memory
//IE: if it's an Int array it would iterate 4 times for every int it changes
