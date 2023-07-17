/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:56:16 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/17 12:51:45 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
}

void	ft_skip_spaces(t_mini *mini, char *str)
{
	while (str[mini->i] && (str[mini->i] == ' ' || str[mini->i] == '\t'))
		mini->i++;
}

void	ft_reset_flag(t_mini *mini)
{
	if (mini->flag_for_pair == 1)
		mini->flag_for_pair = 0;
}

static int	ft_check_if_num_extension(t_mini *mini, char *str, int i, char pair)
{
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if (str[i] != pair)
				mini->exit_flag = 1;
		}
		if (str[i] == pair && mini->flag_for_pair == 1)
			return (0);
		i++;
	}
	return (0);
}

int	ft_check_if_num(t_mini *mini, char *str)
{
	int		i;
	char	pair;

	i = 0;
	pair = '\'';
	if (str[i] == '\'' || str[i] == '"')
	{
		pair = str[i];
		if (ft_look_for_quote(mini, str, 0) == 0)
			mini->exit_flag = 1;
		if (mini->flag_for_pair == 1)
			i++;
	}
	if (str[i] == '-' || str[i] == '+')
		i++;
	ft_check_if_num_extension(mini, str, i, pair);
	return (0);
}
