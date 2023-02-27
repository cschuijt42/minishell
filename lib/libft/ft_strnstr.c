/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:59:46 by cschuijt      #+#    #+#                 */
/*   Updated: 2022/10/12 17:22:11 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);

char	*ft_strnstr(const char *hay, const char *needle, size_t len)
{
	size_t	nlen;

	nlen = ft_strlen(needle);
	if (nlen == 0)
		return ((char *) hay);
	while (*hay && len && len >= nlen)
	{
		if (*hay == *needle && ft_strncmp(hay, needle, nlen) == 0)
			return ((char *) hay);
		hay++;
		len--;
	}
	return (NULL);
}
