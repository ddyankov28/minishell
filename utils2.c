/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:56:22 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/13 12:26:09 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_command_not_found(t_mini *mini, int sw, int i)
{
	mini->space_or_not = 1;
	if (mini->args[i][0] == '\"' && ft_look_for_quote(mini, mini->args[i], 0))
		ft_echo_double(mini, mini->args[i], 0);
	else if (mini->args[i][0] == '\'' && ft_look_for_quote(mini, mini->args[i],
			0))
		ft_echo_single(mini, mini->args[i], 0);
	else
		ft_echo_unclosed(mini, mini->args[i], 0);
	if (sw == 1)
	{
		ft_printf(": Command not found\n");
		mini->exit_value = 127;
	}
	return ;
}

void	ft_write_space(t_mini *mini, int index)
{
	if (mini->space_or_not == 0)
	{
		if (mini->space_flag[index] == 1)
			ft_putchar_fd(' ', 1);
	}
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
			mini->exit_flag = 1;
		if (result * sign < -2147483648)
			mini->exit_flag = 1;
	}
	return (result * sign);
}

void	ft_check_path(t_mini *mini, char *path_env, int sw)
{
	if (ft_strchr(mini->args[0], '/') != NULL)
		execve(mini->args[0], mini->args, mini->env);
	else
	{
		if (!path_env && sw == 0)
			ft_exit_if_no_path(mini);
		else if (!path_env && sw == 1)
		{
			printf("minishell: %s: No such file or directory\n", mini->args[0]);
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
	}
	else
		mini->exit_value = WEXITSTATUS(status);
}
