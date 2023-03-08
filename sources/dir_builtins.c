/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dir_builtins.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 19:38:38 by mde-cloe      #+#    #+#                 */
/*   Updated: 2023/03/08 19:38:38 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

//changed from void to char * ret so it can be used internally, if u dont like
// it this way I can also just make 1 only for printing and put the instructions
// in cd
char	*pwd(bool for_printing)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		error_exit(MAL_ERR, errno);
	if (for_printing)
	{
		printf("%s\n", path);
		//do i need to give a newline??
		free(path);
		return (NULL);
	}
	return (path);
}
// so.. yeah getcwd seems to make this basicly a freebie?
// Idk if there's edgecases that im not thinking of

void	cd(char *path)
{
	if (!path or !*path)
		return
}
//ok so, cd both starting with dir names and ./dirname should function the same
// ./../ is possible though!

// bash cd doesnt go into hidden directories nice
// cd blank space/with no args goes to home folder??