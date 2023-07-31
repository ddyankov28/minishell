/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_input_arguments.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:19:26 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/31 15:23:51 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_count_if_space(t_mini *mini)
{
	while (mini->input[mini->i])
	{
		if (mini->input[mini->i] == ' ' || mini->input[mini->i] == '<'
			|| mini->input[mini->i] == '>' || mini->input[mini->i] == '|')
			break ;
		else if (mini->input[mini->i] == '\'' || mini->input[mini->i] == '"')
		{
			ft_look_for_pair(mini);
			if (mini->flag_for_pair == 1)
			{
				mini->flag_for_pair = 0;
				break ;
			}
		}
		mini->i++;
	}
	mini->argc++;
}

void	ft_count_if_single_quote(t_mini *mini)
{
	ft_look_for_pair(mini);
	while (mini->input[mini->i])
	{
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
	if (mini->flag_for_pair == 1)
		mini->flag_for_pair = 0;
	mini->i++;
	mini->argc++;
}

void	ft_count_if_double_quote(t_mini *mini)
{
	ft_look_for_pair(mini);
	while (mini->input[mini->i])
	{
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
	if (mini->flag_for_pair == 1)
		mini->flag_for_pair = 0;
	mini->i++;
	mini->argc++;
}

void	ft_count_if_redirections(t_mini *mini, char c)
{
	if (c == '<')
	{
		while (mini->input[mini->i] == '<')
			mini->i++;
	}
	else
	{
		while (mini->input[mini->i] == '>')
			mini->i++;
	}
	mini->argc++;
}

void	ft_count_if_pipes(t_mini *mini)
{
	while (mini->input[mini->i] == '|')
		mini->i++;
	mini->argc++;
}
