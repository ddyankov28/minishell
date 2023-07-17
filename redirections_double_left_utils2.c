/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_double_left_utils2.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:33:54 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/17 15:34:32 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_count_double_left(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->args[i])
	{
		if (!ft_strcmp(mini->args[i], "<<"))
			mini->count_heredoc++;
		i++;
	}
}

char *ft_get_path(t_mini *mini)
{
	char *path_env;
	char *path;

	path_env = ft_get_value_from_env(mini->env, "PATH");
	if (path_env != NULL)
	{
		path = ft_strjoin("/bin/", mini->args[0]);
		return (path);
	}
	return (NULL);
}

void	ft_fork_redirections(t_mini *mini)
{
	pid_t pid;
	int  status;
	char *path;

	pid = fork();
	if (!pid)
	{
		path = ft_get_path(mini);
		if (path == NULL)
			exit(1);
		execve(path, mini->exec_arr, mini->env);
	}
	else
	{
		waitpid(pid, &status, 0);
		unlink("/tmp/mini_here_doc_XXXXXX");
	}
}
