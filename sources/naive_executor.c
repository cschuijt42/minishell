/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   naive_executor.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/20 15:29:25 by mde-cloe      #+#    #+#                 */
/*   Updated: 2023/03/20 15:29:25 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

char	**cmd_2_path(char **old_path, char *cmd)
{
	char	**proper_path;
	char	*slash_cmd;
	int		i;

	proper_path = malloc((ptrarr_len((void *)old_path) + 1) * sizeof(char *));
	slash_cmd = ft_strjoin("/", cmd);
	if (!proper_path || !slash_cmd)
		error_exit(MAL_ERR, 1);
		// pipex_exit("malloc fail (go to jail)\n", 12, pipe_fd);
	i = 0;
	while (old_path[i])
	{
		proper_path[i] = ft_strjoin(old_path[i], slash_cmd);
		if (!proper_path[i])
			error_exit(MAL_ERR, 1);
			// pipex_exit("malloc fail (go to jail)\n", 12, pipe_fd);
		free(old_path[i]);
		i++;
	}
	proper_path[i] = NULL;
	free(old_path);
	free(slash_cmd);
	return (proper_path);
}

char	**find_path(char **envp, char *cmd)
{
	int		i;
	char	**path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			// if (ft_strlen(envp[i]) < 6)
			// 	pipex_exit("PATH is unset silly!", 2, pipe_fd);
			path = ft_split(&envp[i][5], ':');
			if (!path)
				error_exit(MAL_ERR, 1);
				// pipex_exit("malloc fail (go to jail)\n", 12, pipe_fd);
			return (cmd_2_path(path, cmd));
		}
		i++;
	}
	// pipex_exit("NO PATH VAR FOUND IN ENV (or exact path)", 2, pipe_fd);
	error_exit("no path found", 1);
	return (NULL);
}

char	**arg_list_to_2dstr(t_argument *head, char *cmd)
{
	char		**str_arr;
	t_argument	*current;
	int			count;

	current = head;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	str_arr = safe_alloc(sizeof(char *), count + 2);
	current = head;
	str_arr[0] = cmd;
	count = 1;
	while (current)
	{
		str_arr[count] = current->content;
		current = current->next;
		count++;
	}
	str_arr[count] = NULL;
	return (str_arr);
}


//first version works! now the main thing will be the structure of forking and
// waiting, and ofcourse the pipes
// not to forget to also work in our dynamic envp list
void	child_process_command(t_command *command, char **envp, int pipe_fd[2])
{
	char	**path;
	char	**args;
	char	*target;

	target = command->target;
	args = arg_list_to_2dstr(command->arguments, target);

	// if (pipe_fd)

	if (ft_strchr(target, '/'))
		execve(target, args, envp);
	path = find_path(envp, target);
	while (*path)
	{
		if (access(*path, F_OK | X_OK) == 0)
		{
			execve(*path, args, envp);
			error_exit("exec fail", 127);
		}
		path++;
	}
	execve(target, args, envp);
}

void	naive_executor(t_shell *shell, char **envp)
{
	t_command	*command_node;
	int			pipe_fd[2][2];

	command_node = shell->command_tree;
	while (command_node)
	{
	// if command->pipes_to
		// pipe(pipe_fd[0]) //add protec
		child_process_command(command_node, envp, pipe_fd[0])

	}
}