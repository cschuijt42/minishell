/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_message.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/03 00:45:15 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/01/03 00:45:15 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

// @brief Prints "Error\n" on stderr, followed by a message, then exits the
// program with code 1.
void	exit_message(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(msg, 2);
	exit(1);
}
