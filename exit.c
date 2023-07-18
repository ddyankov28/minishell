/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:52:41 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/18 14:54:10 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_exit_error(t_mini *mini)
{
	ft_printf("minishell: exit: ");
	ft_write_without_quotes(mini, mini->args[1]);
	ft_printf(": numeric argument required\n");
	ft_free_env_input(mini);
	if (mini->exit_flag == 1)
		exit(2);
	else
		exit(mini->result);
}

static void	ft_exit_2_args(t_mini *mini)
{
	if (mini->args[2] != NULL)
	{
		printf("minishell: exit: too many arguments\n");
		ft_free_env_input(mini);
		exit(2);
	}
}

void	ft_exit(char *input, t_mini *mini)
{
	int	x;

	x = 0;
	free(input);
	ft_printf("exit\n");
	if (mini->args[1] != NULL)
	{
		ft_check_if_num(mini, mini->args[1]);
		ft_delete_quotes_for_str(mini, 1);
		ft_atoi_customize(mini, mini->args[1]);
		ft_exit_2_args(mini);
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
