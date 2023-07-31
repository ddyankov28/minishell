/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:55:49 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/31 14:11:40 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_x(t_mini *mini)
{
	if (mini->args[mini->xx][mini->j] == '$' && (mini->sw_dollar == 0
			|| mini->sw_dollar == 2) && mini->args[mini->xx][mini->j
		+ 1] != '\0')
		return (1);
	return (0);
}

int	ft_swit(t_mini *mini)
{
	while (mini->envvv[mini->env_index] == ' ')
		mini->env_index++;
	while (mini->envvv[mini->env_index] && mini->envvv[mini->env_index] != ' ')
		mini->new_str[mini->in++] = mini->envvv[mini->env_index++];
	if (mini->envvv[mini->env_index] == '\0')
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
	mini->abc = 0;
	mini->not_valid = 1;
	mini->is_redirection = 0;
	mini->z = 0;
	mini->value = NULL;
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

int	ft_valid_or_not(t_mini *mini, int i)
{
	int	j;

	j = 0;
	if (mini->args[i][0] == '\'' || mini->args[i][0] == '\"')
	{
		if (ft_look_for_quote(mini, mini->args[i], j) == 1 && mini->space_flag[i
				- 1] == 0)
			return (0);
	}
	if (mini->space_flag[i - 1] == 0)
		return (0);
	while (mini->args[i][j])
	{
		if ((mini->args[i][j] >= 33 && mini->args[i][j] <= 47)
			|| (mini->args[i][j] >= 58 && mini->args[i][j] <= 64)
			|| (mini->args[i][j] >= 91 && mini->args[i][j] <= 96)
			|| (mini->args[i][j] >= 123 && mini->args[i][j] <= 126))
		{
			mini->export_sw++;
			mini->not_valid = i;
			return (1);
		}
		j++;
	}
	return (0);
}
