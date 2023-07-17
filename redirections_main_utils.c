/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_main_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:20:46 by ddyankov          #+#    #+#             */
/*   Updated: 2023/07/17 21:27:29 by ddyankov         ###   ########.fr       */
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
	perror("Temp file error");
	free(mini->space_flag);
	ft_free_2d_arr(mini->env);
	ft_free_2d_arr(mini->args);
	mini->exit_value = 1;
	exit(1);
}
