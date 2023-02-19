/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 15:57:53 by cschuijt      #+#    #+#                 */
/*   Updated: 2022/10/12 17:23:17 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>

size_t		ft_strlen(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		*ft_calloc(size_t nmemb, size_t size);

static int	ft_is_in_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (true);
		set++;
	}
	return (false);
}

static size_t	ft_match_start(char const *s1, char const *set)
{
	size_t	offset;

	offset = 0;
	while (*s1 && ft_is_in_set(*s1, set))
	{
		offset++;
		s1++;
	}
	return (offset);
}

static size_t	ft_match_end(char const *s1, char const *set)
{
	size_t	offset;
	size_t	len;

	offset = 0;
	len = ft_strlen(s1);
	s1 = s1 + ft_strlen(s1) - 1;
	while (offset < len && ft_is_in_set(*s1, set))
	{
		offset++;
		s1--;
	}
	return (offset);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	offset_start;
	size_t	offset_end;
	size_t	len;

	offset_start = ft_match_start(s1, set);
	offset_end = ft_match_end(s1, set);
	if ((offset_start + offset_end) >= ft_strlen(s1))
		return (ft_calloc(sizeof(char), 1));
	len = ft_strlen(s1) - offset_end - offset_start;
	return (ft_substr(s1, (unsigned int) offset_start, len));
}
