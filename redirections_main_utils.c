/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_main_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:20:46 by ddyankov          #+#    #+#             */
/*   Updated: 2023/07/25 10:36:59 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_get_path(t_mini *mini)
{
	char	*path_env;
	char	*path;

	path_env = ft_get_value_from_env(mini->env, "PATH");
	if (path_env != NULL)
	{
		if (ft_strchr(mini->args[0], '/') != NULL)
		{
			path = ft_strdup(mini->args[0]);
			return (path);
		}
		path = ft_strjoin("/bin/", mini->args[0]);
		return (path);
	}
	return (NULL);
}

void	ft_fork_redirections(t_mini *mini)
{
	pid_t	pid;
	int		status;
	char	*path;

	pid = fork();
	if (pid == -1)
		ft_fork_error();
	else if (!pid)
	{
		path = ft_get_path(mini);
		if (!path)
			ft_no_path(mini);
		if (execve(path, mini->exec_arr, mini->env) == -1)
		{
			free(path);
			ft_execve_error(mini);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (status == 256)
			mini->exit_value = 127;
		unlink("/tmp/mini_here_doc_XXXXXX");
	}
}

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

void	ft_input_fd(t_mini *mini)
{
	int	i;

	i = 0;
	perror("Temp file error");
	while (i < mini->index)
	{
		free(mini->args[i]);
		i++;
	}
	free(mini->args);
	ft_free_2d_arr(mini->env);
	ft_free_2d_arr(mini->exec_arr);
	free(mini->space_flag);
	mini->exit_value = 1;
	exit(1);
}
