/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:50:31 by ddyankov          #+#    #+#             */
/*   Updated: 2023/07/17 12:15:03 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_create_pipes(t_mini *mini, int *pipe_fds)
{
	int	i;
	int	num_com;

	num_com = mini->num_commands;
	i = 0;
	while (i < num_com)
	{
		if (pipe(pipe_fds + i * 2) < 0)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	ft_close_pipes(int num_commands, int *pipe_fds)
{
	int	j;

	j = 0;
	while (j < 2 * num_commands)
	{
		close(pipe_fds[j]);
		j++;
	}
}

void	ft_output(t_mini *mini, int i, int num_commands, int *pipe_fds)
{
	if (mini->output_fd != -1)
	{
		mini->stdout_copy = dup(STDOUT_FILENO);
		dup2(mini->output_fd, STDOUT_FILENO);
		close(mini->output_fd);
	}
	else if (mini->append_fd != -1)
	{
		mini->stdout_copy = dup(STDOUT_FILENO);
		dup2(mini->append_fd, STDOUT_FILENO);
		close(mini->append_fd);
	}
	else if (i != num_commands - 1)
	{
		dup2(pipe_fds[i * 2 + 1], 1);
	}
}

void	ft_input(t_mini *mini, int i, int *pipe_fds)
{
	if (mini->input_fd != -1)
	{
		mini->stdin_copy = dup(STDIN_FILENO);
		dup2(mini->input_fd, STDIN_FILENO);
		close(mini->input_fd);
	}
	else if (i != 0)
	{
		dup2(pipe_fds[(i - 1) * 2], 0);
	}
}

void	ft_dup_child(t_mini *mini, int i, int num_commands, int *pipe_fds)
{
	ft_input(mini, i, pipe_fds);
	ft_output(mini, i, num_commands, pipe_fds);
}
