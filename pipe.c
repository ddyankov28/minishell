/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:50:50 by ddyankov          #+#    #+#             */
/*   Updated: 2023/07/31 15:47:48 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_check_for_double_left_redirection(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->commands[i])
	{
		if (ft_strnstr(mini->commands[i], "<<", 100) != NULL)
			mini->red_left++;
		i++;
	}
}

int	ft_execute_pipes(t_mini *mini)
{
	ft_split_into_commands(mini);
	mini->num_commands = ft_len_2d_arr(mini->commands);
	mini->pipe_fds = malloc(sizeof(int) * (2 * mini->num_commands));
	if (!mini->pipe_fds)
	{
		free(mini->pipe_fds);
		ft_free_malloc(mini);
	}
	ft_create_pipes(mini, mini->pipe_fds);
	ft_check_for_double_left_redirection(mini);
	ft_fork_for_commands(mini, mini->pipe_fds);
	ft_close_pipes(mini->num_commands, mini->pipe_fds);
	ft_wait_for_processes(mini, mini->num_commands);
	if (mini->red_left > 0)
		unlink("/tmp/mini_here_doc_XXXXXX");
	free(mini->pipe_fds);
	ft_free_2d_arr(mini->commands);
	free(mini->pid_fork);
	return (0);
}

void	ft_fork_for_commands(t_mini *mini, int *pipe_fds)
{
	int	i;

	i = 0;
	mini->pid_fork = malloc(sizeof(int) * mini->num_commands);
	if (!mini->pid_fork)
	{
		free(mini->pid_fork);
		ft_free_malloc(mini);
	}
	while (i < mini->num_commands)
	{
		mini->pid_fork[i] = fork();
		signal(SIGINT, SIG_IGN);
		if (mini->pid_fork[i] < 0)
			ft_fork_error();
		else if (!mini->pid_fork[i])
		{
			signal(SIGINT, SIG_DFL);
			ft_fork_for_commands_extension(mini, i, pipe_fds);
		}
		i++;
	}
}

void	ft_fork_for_commands_extension(t_mini *mini, int i, int *pipe_fds)
{
	char	*path;

	mini->input = mini->commands[i];
	ft_split_input(mini);
	ft_redirections_change_position(mini, 1);
	if (!ft_check_for_redirection(mini))
	{
		free(pipe_fds);
		ft_free_when_forked(mini);
	}
	ft_dup_child(mini, i, mini->num_commands, pipe_fds);
	ft_close_pipes(mini->num_commands, pipe_fds);
	free(pipe_fds);
	if (mini->here > 0)
	{
		path = ft_get_path(mini);
		if (path == NULL)
			exit(1);
		execve(path, mini->exec_arr, mini->env);
		exit(0);
	}
	if (mini->is_redirection == 0)
		ft_expand(mini);
	ft_execute_built_in_command(mini, mini->args);
	ft_search_and_execute(mini, 1);
}

void	ft_wait_for_processes(t_mini *mini, int num_commands)
{
	int	i;
	int	status;

	i = 0;
	while (i < num_commands)
	{
		waitpid(mini->pid_fork[i], &status, 0);
		if (status == 256 || status == 4)
			mini->exit_value = 127;
		else if (status == 2)
		{
			if (i == 0)
			{
				write(1, "\n", 1);
				mini->exit_value = 130;
			}
		}
		else
			mini->exit_value = WEXITSTATUS(status);
		i++;
	}
}
