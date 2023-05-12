/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_dir.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 19:38:38 by mde-cloe      #+#    #+#                 */
/*   Updated: 2023/03/08 19:38:38 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

#define CHDIR_ERROR	"\x1b[38;2;255;192;128m\x1b[1m \
cd? more like c deez error messages haHA\x1b[0m"

//changed from void to char * ret so it can be used internally, if u dont like
// it this way I can also just make 1 only for printing and put the instructions
// in cd
// 3/4 update.. yeah I might refactor this cause I can just call getcwd
int	pwd(t_argument *args, t_shell *shell)
{
	(void) args;
	if (!getcwd(shell->cwd, PATH_MAX))
	{
		perror("can't get working dir");
		return (1);
	}
	printf("%s\n", shell->cwd);
	return (0);
}

int	cd(t_argument *args, t_shell *shell)
{
	char	*new_dir;

	new_dir = NULL;
	if (!getcwd(shell->cwd, PATH_MAX) || access(shell->cwd, F_OK) != 0)
	{
		perror(C_RED "current dir destroyed, I'm going HOME >:c\n" C_RESET);
		args = NULL;
	}
	if (!args)
		new_dir = get_env_var_value("HOME", shell->environment);
	else if (args->content && args->content[0] == '-' && !args->content[1])
		new_dir = get_env_var_value("OLDPWD", shell->environment);
	if (!new_dir || !*new_dir)
		dprintf(2, C_RED " you can't cd to your HOME or OLDPWD if its not set silly! \
				\n" C_RESET);
	if (chdir(new_dir) == -1)
		perror(CHDIR_ERROR);
	// Change PWD and OLDPWD
	return (0);
}
// EDGECASE deleting current dir and then cding
// solve by access checking first->if false cd OLDPWD if false cd HOME if false
// then cmon bro then your minishell wouldnt even be there anymore
