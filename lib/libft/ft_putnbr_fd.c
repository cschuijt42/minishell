/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 15:18:19 by cschuijt      #+#    #+#                 */
/*   Updated: 2022/10/14 13:09:39 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	write_number(int n, int fd)
{
	char	c;

	if (n < -9)
		write_number(n / 10, fd);
	if (n < 0)
	{
		c = 48 - (n % 10);
		write(fd, &c, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		write(fd, "-", 1);
	else
		n = n * -1;
	if (n == 0)
		write(fd, "0", 1);
	write_number(n, fd);
}
