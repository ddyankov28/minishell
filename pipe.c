/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:50:50 by ddyankov          #+#    #+#             */
/*   Updated: 2023/07/14 14:44:21 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_execute_pipes(t_mini *mini)
{
	if ((!ft_strcmp(mini->args[0], "cat") && !mini->args[1])
		|| (!ft_strcmp(mini->args[0], "grep") && mini->args[1]))
		mini->new_line = 1;
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
	pid_t	pid;

	i = 0;
	while (i < mini->num_commands)
	{
		pid = fork();
		mini->pid_fork = pid;
		signal(SIGINT, SIG_IGN);
		if (pid < 0)
		{
			perror("Fork Error");
			exit(EXIT_FAILURE);
		}
		else if (!pid)
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
	while (i < num_commands - 1)
	{
		wait(NULL);
		i++;
	}
	waitpid(mini->pid_fork, &status, 0);
	printf("%d", status);
	if (status == 256 || status == 4)
		mini->exit_value = 127;
	else if (status == 2)
	{
		write(1, "\n", 1);
		mini->exit_value = 130;
	}
	else
		mini->exit_value = WEXITSTATUS(status);
}
