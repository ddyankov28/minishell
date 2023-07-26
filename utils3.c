/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:55:49 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/26 12:59:11 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_swit(t_mini *mini)
{
	while (mini->envvv[mini->env_index] == ' ')
		mini->env_index++;
	while (mini->envvv[mini->env_index] && mini->envvv[mini->env_index] != ' ')
		mini->new_str[mini->in++] = mini->envvv[mini->env_index++];
	mini->swit = 0;
	return (1);
}

static int	ft_init_another_struct(t_mini *mini)
{
	mini->xx = 0;
	mini->swit = 0;
	mini->j = 0;
	mini->env_index = 0;
	mini->sw_dollar = 0;
	mini->a = 0;
	mini->in = 0;
    return (0);
}

void	ft_init_struct(t_mini *mini)
{
	mini->input_fd = -1;
	mini->output_fd = -1;
	mini->append_fd = -1;
	mini->stdin_copy = -1;
	mini->stdout_copy = -1;
	mini->index = 0;
	mini->flag_for_pair = 0;
	mini->exit_flag = 0;
	mini->i = 0;
	mini->argc = 0;
	mini->space_or_not = 0;
	mini->export_sw = 0;
	mini->count = 0;
	mini->count_heredoc = 0;
	mini->here = 0;
	mini->red_left = 0;
	mini->result = 0;
	mini->fd = 1;
	mini->output_len = 0;
	mini->redirection_count = 0;
	mini->plus = 0;
	ft_init_another_struct(mini);
}
