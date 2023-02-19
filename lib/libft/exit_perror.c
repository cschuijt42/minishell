/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_perror.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/03 00:46:11 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/01/03 00:46:11 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

// @brief Calls perror with msg, then exits the program with code 1.
void	exit_perror(char *msg)
{
	perror(msg);
	exit(1);
}
