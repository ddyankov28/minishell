/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:50:50 by ddyankov          #+#    #+#             */
/*   Updated: 2023/07/17 10:09:25 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
	ft_fork_for_commands(mini, mini->pipe_fds);
	ft_close_pipes(mini->num_commands, mini->pipe_fds);
	ft_wait_for_processes(mini, mini->num_commands);
	free(mini->pipe_fds);
	ft_free_2d_arr(mini->commands);
	return (0);
}

void	ft_fork_for_commands(t_mini *mini, int *pipe_fds)
{
	int		i;

	i = 0;
	mini->pid_fork = malloc(sizeof(int) * mini->num_commands);
	while (i < mini->num_commands)
	{
		mini->pid_fork[i] = fork();
		signal(SIGINT, SIG_IGN);
		if (mini->pid_fork[i] < 0)
		{
			perror("Fork Error");
			exit(EXIT_FAILURE);
		}
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
	mini->input = mini->commands[i];
	ft_split_input(mini);
	ft_check_for_redirection(mini);
	ft_dup_child(mini, i, mini->num_commands, pipe_fds);
	ft_close_pipes(mini->num_commands, pipe_fds);
	free(pipe_fds);
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
