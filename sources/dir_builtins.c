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
int	pwd(t_argument *args, t_shell *shell)
{
	char	*path;

	(void) args;
	(void) shell;
	path = getcwd(NULL, 0);
	if (!path)
		error_exit(MAL_ERR, errno);
	printf("%s\n", path);
	//do i need to give a newline??
	// set PWD in ENVP!
	free(path);
	return (0);
}
// so.. yeah getcwd seems to make this basicly a freebie?
// Idk if there's edgecases that im not thinking of

int	cd(t_argument *args, t_shell *shell)
{
	char	current_dir[PATH_MAX];
	char	*new_dir;

	new_dir = NULL;
	if (!getcwd(current_dir, PATH_MAX) || access(current_dir, F_OK) != 0)
	{
		perror(C_RED "current dir destroyed, I'm going HOME >:c\n" C_RESET);
		args = NULL;
	}
	if (!args)
		new_dir = get_env_var_value("HOME", shell->environment); //should be new alloc
	//other arguments just get ignored by bash :)
	else if (args->content && args->content[0] == '-' && !args->content[1])
		new_dir = get_env_var_value("OLDPWD", shell->environment);
	if (!new_dir || !*new_dir)
		dprintf(2, C_RED " you can't cd to your HOME or OLDPWD if its not set silly! \
				\n" C_RESET);
	if (chdir(new_dir) == -1)
		perror(CHDIR_ERROR);
	//set new PWD and old PWD
	return (0);
}
// EDGECASE deleting current dir and then cding
// solve by access checking first->if false cd OLDPWD if false cd HOME if false
// then cmon bro then your minishell wouldnt even be there anymore

int	builtin_exit(t_argument *args, t_shell *shell)
{
	(void)shell; //do we have to free before exiting?
	printf("exit\n");
	if (args && args->content)
		exit(ft_atoi(args->content)); //custom atoi that protects against >230 overflow?
	exit(10);
}

int	echo(t_argument *args, t_shell *shell)
{
	(void)args;
	(void)shell;
	return (0);
}

void	print_alphabet(char **envp)
{
	int		i;
	int		arrlen;
	char	**copy;
	char	*temp;

	i = 0;
	arrlen = ptrarr_len((void **)envp);
	copy = safe_alloc(sizeof(char *), arrlen);
	ft_memcpy(copy, envp, sizeof(char *) * arrlen);
	while (arrlen)
	{
		while (copy[i + 1] && i + 1 < arrlen)
		{
			if (ft_strcmp(copy[i], copy[i + 1]) > 0)
				str_switch(&copy[i], &copy[i + 1]);
			i++;
		}
		arrlen--;
		i = 0;
	}
	print_2d_charray(copy);
	free(copy);
}

int	export(t_argument *args, t_shell *shell)
{
	if (!args)
		print_alphabet(shell->envp); //sort alphabetically?
	else if (!ft_strchr(args->content, (int) '='))
	{
		puts("placeholder"); //can put
	}
	return (0);
}

int	env(t_argument *args, t_shell *shell)
{
	(void)args;
	(void)shell;
	print_2d_charray(shell->envp);
	return (0);
}
//ok so, cd both starting with dir names and ./dirname should function the same
// ./../ is possible though!

// bash cd doesnt go into hidden directories nice
// cd blank space/with no args goes to home folder??

// https://man7.org/linux/man-pages/man1/cd.1p.html


void	remove_node_and_remake_env(t_env_list *remove_me, t_shell *shell)
{
	t_env_list	*current;

	current = shell->environment;
	if (current != remove_me)
	{
		while (current->next != remove_me)
			current = current->next;
		current->next = current->next->next;
	}
	else
		shell->environment = remove_me->next;
	free(remove_me->key);
	free(remove_me->value);
	free(remove_me);
	free_array((void **)shell->envp);
	shell->envp = env_list_to_arr(shell->environment);
}

void	find_env_var(char *key, t_shell *shell)
{

	t_env_list	*list;

	list = shell->environment;
	while (list && ft_strncmp(key, list->key, ft_strlen(key)))
		list = list->next;
	if (list)
		remove_node_and_remake_env(list, shell);
} //wanted to finish but was getting too late, this could be 1 fun w the 1 above

int	unset(t_argument *args, t_shell *shell)
{
	t_env_list	*node;
	bool		err_occured;

	err_occured = false;
	while (args)
	{
		node = shell->environment;
		if (!str_is_fully_alnum(args->content))
		{
			dprintf(2, "you" C_RED "set" C_RESET "yourself up for failure\n\
					%s is not a valid identifier\n", args->content);
			err_occured = true;
		}
		else
		{
			while (node)
			{
				if (!ft_strcmp(args->content, node->key))
				{
					remove_node_and_remake_env(node, shell);
					break ; //could remove for more readablity but less performance
				}
				node = node->next;
			}
		}
		args = args->next;
	}
	if (err_occured)
		return (1);
	return (0);
}
