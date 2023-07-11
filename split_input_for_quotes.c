/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input_for_quotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:49:15 by vstockma          #+#    #+#             */
/*   Updated: 2023/06/28 17:19:30 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_split_double_quotes(t_mini *mini)
{
	int	j;

	j = 0;
	mini->args[mini->index] = malloc(sizeof(char)
			* (ft_get_len_if_double(mini->input, mini->i) + 1));
	if (!mini->args[mini->index])
		ft_free_malloc(mini);
	ft_look_for_pair(mini);
	while (mini->input[mini->i])
	{
		mini->args[mini->index][j] = mini->input[mini->i];
		j++;
		mini->i++;
		if (mini->input[mini->i] == '"')
			break ;
		else if ((mini->input[mini->i] == '<' || mini->input[mini->i] == '>'
				|| mini->input[mini->i] == '|') && mini->flag_for_pair == 0)
			break ;
		else if (mini->input[mini->i] == '\'' && mini->flag_for_pair == 0
			&& ft_look_for_pair_in_pair(mini) == 1)
			break ;
	}
	ft_single_and_double_extension(mini, j, 1);
	ft_handle_spaceflag(mini, 2);
	mini->index++;
}

void	ft_split_single_quotes(t_mini *mini)
{
	int	j;

	j = 0;
	mini->args[mini->index] = malloc(sizeof(char)
			* (ft_get_len_if_single(mini->input, mini->i) + 1));
	if (!mini->args[mini->index])
		ft_free_malloc(mini);
	ft_look_for_pair(mini);
	while (mini->input[mini->i])
	{
		mini->args[mini->index][j] = mini->input[mini->i];
		j++;
		mini->i++;
		if (mini->input[mini->i] == '\'')
			break ;
		else if ((mini->input[mini->i] == '<' || mini->input[mini->i] == '>'
				|| mini->input[mini->i] == '|') && mini->flag_for_pair == 0)
			break ;
		else if (mini->input[mini->i] == '"' && mini->flag_for_pair == 0
			&& ft_look_for_pair_in_pair(mini) == 1)
			break ;
	}
	ft_single_and_double_extension(mini, j, 2);
	ft_handle_spaceflag(mini, 2);
	mini->index++;
}

void	ft_single_and_double_extension(t_mini *mini, int j, int x)
{
	if (x == 1)
	{
		if (mini->flag_for_pair == 1)
		{
			mini->flag_for_pair = 0;
			mini->args[mini->index][j] = '"';
			mini->i++;
			j++;
		}
		mini->args[mini->index][j] = '\0';
	}
	else
	{
		if (mini->flag_for_pair == 1)
		{
			mini->flag_for_pair = 0;
			mini->args[mini->index][j] = '\'';
			j++;
			mini->i++;
		}
		mini->args[mini->index][j] = '\0';
	}
}
