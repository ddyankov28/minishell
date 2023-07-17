/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:38:04 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/17 14:39:19 by vstockma         ###   ########.fr       */
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
