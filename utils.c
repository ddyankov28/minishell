/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:56:16 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/26 12:58:01 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
