/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:38:04 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/21 11:39:01 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

void	ft_ctrl_d(t_mini *mini)
{
	if (!mini->input)
	{
		printf("exit\n");
		free(mini->input);
		ft_free_2d_arr(mini->env);
		exit(0);
	}
}

void	ft_write_space(t_mini *mini, int index)
{
	if (mini->space_or_not == 0)
	{
		if (mini->space_flag[index] == 1)
			ft_putchar_fd(' ', mini->fd);
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
