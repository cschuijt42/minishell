/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 16:15:16 by cschuijt      #+#    #+#                 */
/*   Updated: 2022/10/06 11:49:08 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

int	ft_isalpha(int c)
{
	if (c >= 65 && c <= 90)
		return (true);
	if (c >= 97 && c <= 122)
		return (true);
	return (false);
}
