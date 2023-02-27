/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_base.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 17:02:59 by cschuijt      #+#    #+#                 */
/*   Updated: 2022/10/24 17:49:52 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_put_nbr_base(size_t n, char *base)
{
	size_t	bl;
	int		i;

	bl = ft_strlen(base);
	if (n > bl)
		ft_put_nbr_base(n / bl, base);
	write(1, &base[n % bl], 1);
	i = 0;
	while (n)
	{
		n /= bl;
		i++;
	}
	return (i);
}
