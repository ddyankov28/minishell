/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:56:22 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/17 22:22:39 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_command_not_found_loop(t_mini *mini, int i)
{
	mini->fd = STDERR_FILENO;
	while (mini->args[i])
	{
		mini->space_or_not = 1;
		if (mini->args[i][0] == '\"' && ft_look_for_quote(mini, mini->args[i],
			0))
			ft_echo_double(mini, mini->args[i], 0);
		else if (mini->args[i][0] == '\'' && ft_look_for_quote(mini,
			mini->args[i], 0))
			ft_echo_single(mini, mini->args[i], 0);
		else
			ft_echo_unclosed(mini, mini->args[i], 0);
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
		if (mini->args[0][0] == '$')
		{
			if (mini->args[1] != NULL)
			{
				ft_putstr_fd(mini->args[1], mini->fd);
				ft_putendl_fd(": Command not found", mini->fd);
				mini->exit_value = 127;
				return ;
			}
			mini->exit_value = 0;
			return ;
		}
		ft_putendl_fd(": Command not found", mini->fd);
		mini->exit_value = 127;
	}
	mini->fd = 1;
	return ;
}

int	ft_atoi_customize(t_mini *mini, const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + str[i] - 48;
		i++;
		if (result * sign > 2147483647)
			mini->exit_flag = 2;
		if (result * sign < -2147483648)
			mini->exit_flag = 2;
	}
	mini->result = result * sign;
	return (result * sign);
}

void	ft_check_path(t_mini *mini, char *path_env, int sw)
{
	if (ft_strchr(mini->args[0], '/') != NULL)
	{
		if (access(mini->args[0], F_OK | X_OK) == 0)
		{
			execve(mini->args[0], mini->args, mini->env);
			exit(1);
		}
		printf("minishell: %s: Permission denied\n", mini->args[0]);
		exit(126);
	}
	else
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
}

void	ft_check_status(t_mini *mini, int status)
{
	if (status == 2)
	{
		mini->exit_value = 130;
		g_exit_status = 130;
		write(1, "\n", 1);
	}
	if (status == 131)
	{
		write(1, "Quit (core dumped)\n", 20);
		mini->exit_value = 131;
	}
	else
		mini->exit_value = WEXITSTATUS(status);
}
