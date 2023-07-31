/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:00:40 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/31 15:43:24 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_swap_arguments(t_mini *mini)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	tmp = ft_strdup(mini->args[i]);
	while (i < mini->index - 1)
	{
		free(mini->args[i]);
		mini->args[i] = ft_strdup(mini->args[i + 1]);
		i++;
	}
	free(mini->args[i]);
	mini->args[i] = ft_strdup(tmp);
	free(tmp);
	return (0);
}

void	ft_redirections_change_position(t_mini *mini, int sw)
{
	if (sw == 0)
	{
		if (ft_check_if_pipe(mini->args) != 1)
		{
			if (!ft_strcmp(mini->args[0], "<") || !ft_strcmp(mini->args[0], ">")
				|| !ft_strcmp(mini->args[0], ">>") || !ft_strcmp(mini->args[0],
					"<<"))
			{
				ft_swap_arguments(mini);
				ft_swap_arguments(mini);
			}
		}
	}
}

void	ft_look_for_pair(t_mini *mini)
{
	char	pair_char;
	int		i;

	i = mini->i;
	pair_char = mini->input[i];
	i++;
	while (mini->input[i])
	{
		if (mini->input[i] == pair_char)
		{
			mini->flag_for_pair = 1;
			break ;
		}
		i++;
	}
}

int	ft_look_for_pair_in_pair(t_mini *mini)
{
	char	pair_char;
	int		i;

	i = mini->i;
	pair_char = mini->input[i];
	i++;
	while (mini->input[i])
	{
		if (mini->input[i] == pair_char)
			return (1);
		i++;
	}
	return (0);
}

int	ft_look_for_quote(t_mini *mini, char *str, int i)
{
	char	pair_char;

	ft_reset_flag(mini);
	pair_char = str[i];
	i++;
	while (str[i])
	{
		if (str[i] == pair_char)
		{
			mini->flag_for_pair = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
