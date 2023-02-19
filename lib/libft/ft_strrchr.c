/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/09 11:28:03 by cschuijt      #+#    #+#                 */
/*   Updated: 2022/10/17 17:17:04 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *s);

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	s = s + i;
	while (i > 0)
	{
		if ((unsigned char) *s == (unsigned char) c)
			return ((char *) s);
		s--;
		i--;
	}
	if ((unsigned char) c == *s)
		return ((char *) s);
	else
		return (NULL);
}
