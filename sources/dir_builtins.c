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

#define CHDIR_ERROR	"\x1b[38;2;255;192;128m\x1b[1m \
cd? more like c deez error messages haHA\x1b[0m"

//changed from void to char * ret so it can be used internally, if u dont like
// it this way I can also just make 1 only for printing and put the instructions
// in cd
// 3/4 update.. yeah I might refactor this cause I can just call getcwd
void	pwd(char **args, t_shell *shell)
{
	char	*path;

	(void)shell;
	path = getcwd(NULL, 0);
	if (!path)
		error_exit(MAL_ERR, errno);
	printf("%s\n", path);
	//do i need to give a newline??
	free(path);
}
// so.. yeah getcwd seems to make this basicly a freebie?
// Idk if there's edgecases that im not thinking of

void	cd(char **path, t_shell *shell)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (access(current_dir, F_OK) != 0)
	{
		printf("hoi"); //go into
	}
	if (!path || !*path)
		path = get_env_var_value("HOME", shell->environment);
	else if (*path == '-' && !path[1])
		path = get_env_var_value("OLDPWD", shell->environment);
	if (!path || !*path)
		dprintf(2, "%s you can't cd to your HOME or OLDPWD if its not set silly! \
				%s\n", C_RED, C_RESET);
	if (chdir(path) == -1)
		perror(CHDIR_ERROR);
		// path = getenv("HOME");
		// path = getenv("OLDPWD");
	return ;
}
// EDGECASE deleting current dir and then cding
// solve by access checking first->if false cd OLDPWD if false cd HOME if false
// then cmon bro then your minishell wouldnt even be there anymore

void	builtin_exit(char **code, t_shell *shell)
{
	(void)shell; //do we have to free before exiting?
	printf("exit\n");
	if (code && *code)
		exit(ft_atoi(code)); //custom atoi that protects against >230 overflow?
	exit(10);
}

void	echo(char **text, t_shell *shell)
{
	(void)text;
	(void)shell;
}

void	export(char **env_line, t_shell *shell)
{
	(void)shell;
	if (!ft_strchr(env_line, (int) '='))
	{
		puts("placeholder");
	}
}

void	env(char **hoi, t_shell *shell)
{
	(void)hoi;
	(void)shell;
}
//ok so, cd both starting with dir names and ./dirname should function the same
// ./../ is possible though!

// bash cd doesnt go into hidden directories nice
// cd blank space/with no args goes to home folder??

// https://man7.org/linux/man-pages/man1/cd.1p.html
