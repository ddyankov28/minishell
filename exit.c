/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:52:41 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/22 13:31:11 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	ft_atoi_customize(t_mini *mini, const char *str)
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

static void	ft_exit_error(t_mini *mini)
{
	ft_printf("minishell: exit: ");
	ft_write_without_quotes(mini, mini->args[1]);
	ft_printf(": numeric argument required\n");
	ft_free_env_input(mini);
	exit(2);
}

static int	ft_exit_2_args(t_mini *mini)
{
	int	x;
	int	i;

	i = 0;
	x = 0;
	while (mini->args[1][i])
	{
		if (!ft_isdigit(mini->args[1][i]))
			x = 1;
		i++;
	}
	if (mini->args[2] != NULL && x == 0)
	{
		printf("minishell: exit: too many arguments\n");
		mini->exit_value = 1;
		return (1);
	}
	return (0);
}

void	ft_exit(char *input, t_mini *mini)
{
	int	x;

	x = 0;
	ft_printf("exit\n");
	if (mini->args[1] != NULL)
	{
		ft_check_if_num(mini, mini->args[1]);
		ft_delete_quotes_for_str(mini, 1);
		ft_atoi_customize(mini, mini->args[1]);
		if (ft_exit_2_args(mini) == 1)
			return ;
		free(input);
		if (mini->exit_flag != 0)
			ft_exit_error(mini);
		else
		{
			ft_free_2d_arr(mini->env);
			x = ft_atoi(mini->args[1]);
			ft_free_input(mini);
			rl_clear_history();
			exit(x);
		}
	}
	ft_free_env_input(mini);
	exit(mini->exit_value);
}
