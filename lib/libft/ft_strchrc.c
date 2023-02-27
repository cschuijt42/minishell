/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchrc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 13:12:10 by cschuijt      #+#    #+#                 */
/*   Updated: 2022/11/17 13:12:10 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strchrc(char *str, char c)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}
