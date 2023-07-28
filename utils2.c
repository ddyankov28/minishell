/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:56:22 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/28 13:55:17 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_command_not_found_loop(t_mini *mini, int i)
{
	mini->fd = STDERR_FILENO;
	while (mini->args[i])
	{
		mini->space_or_not = 1;
		ft_putstr_fd(mini->args[i], mini->fd);
		if (mini->space_flag[i] != 0)
			break ;
		i++;
	}
}

void	ft_command_not_found(t_mini *mini, int sw, int i)
{
	ft_command_not_found_loop(mini, i);
	if (sw == 1)
	{
		ft_putendl_fd(": command not found", mini->fd);
		mini->exit_value = 127;
	}
	mini->fd = 1;
	return ;
}

static void	ft_check_path_if(t_mini *mini, char *path_env, int sw)
{
	if (access(mini->args[0], F_OK | X_OK) == 0)
	{
		execve(mini->args[0], mini->args, mini->env);
		exit(1);
	}
	if (!path_env && sw == 0)
		ft_exit_if_no_path(mini);
	else if (!path_env && sw == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(mini->args[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
		ft_free_when_forked(mini);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(mini->args[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
		ft_free_input(mini);
		ft_free_2d_arr(mini->env);
		exit(2);
	}
}

static void	ft_help_me(t_mini *mini, char *path_env, int sw)
{
	if (!path_env && sw == 0)
		ft_exit_if_no_path(mini);
	else if (!path_env && sw == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(mini->args[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
		ft_free_when_forked(mini);
	}
}

void	ft_check_path(t_mini *mini, char *path_env, int sw)
{
	int	file_exists;

	file_exists = 0;
	file_exists = open(mini->args[0], O_RDONLY);
	if (ft_strchr(mini->args[0], '/') != NULL)
	{
		if (file_exists != -1 || errno == EACCES || errno == EPERM)
		{
			if (file_exists != -1)
				close(file_exists);
			if (access(mini->args[0], F_OK | X_OK) == 0)
				ft_yes_directory(mini);
			printf("minishell: %s: Permission denied\n", mini->args[0]);
			ft_free_2d_arr(mini->env);
			ft_free_input(mini);
			exit(126);
		}
		else
			ft_check_path_if(mini, path_env, sw);
	}
	else
		ft_help_me(mini, path_env, sw);
}
