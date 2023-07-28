/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:47:52 by ddyankov          #+#    #+#             */
/*   Updated: 2023/07/28 12:39:52 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_free_input(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < mini->index)
	{
		if (mini->args[i] != NULL)
			free(mini->args[i]);
		i++;
	}
	free(mini->args);
	free(mini->space_flag);
	if (mini->here > 0)
		ft_free_2d_arr(mini->exec_arr);
	mini->index = 0;
}

void	ft_free_result_commands(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < mini->num_commands)
	{
		free(mini->commands[i]);
		i++;
	}
	free(mini->commands);
}

void	ft_free_when_forked(t_mini *mini)
{
	ft_free_2d_arr(mini->commands);
	ft_free_2d_arr(mini->env);
	ft_free_input(mini);
	free(mini->pid_fork);
	ft_restore_and_close_fds(mini);
	exit(EXIT_FAILURE);
}

void	ft_free_malloc(t_mini *mini)
{
	int	i;

	i = 0;
	while (i <= mini->index)
	{
		free(mini->args[i]);
		i++;
	}
	free(mini->args);
	free(mini->space_flag);
	ft_free_2d_arr(mini->env);
	printf("Allocation failed\n");
	exit(EXIT_FAILURE);
}

void	ft_free_env_input(t_mini *mini)
{
	ft_free_2d_arr(mini->env);
	ft_free_input(mini);
}
