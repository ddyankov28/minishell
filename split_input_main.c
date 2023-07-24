/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:29:34 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/24 11:22:21 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	ft_loop_input_string(t_mini *mini)
{
	while (mini->input[mini->i])
	{
		if (ft_check_multiple_redirections(mini) == 1)
			return (1);
		ft_skip_spaces(mini, mini->input);
		if (mini->input[mini->i] == '\0')
			break ;
		if (mini->input[mini->i] == '\'')
			ft_split_single_quotes(mini);
		else if (mini->input[mini->i] == '"')
			ft_split_double_quotes(mini);
		else if (mini->input[mini->i] == '<' || mini->input[mini->i] == '>')
			ft_split_redirections(mini, mini->input[mini->i]);
		else if (mini->input[mini->i] == '|')
			ft_split_pipes(mini);
		else
			ft_split_space(mini);
	}
	if (ft_check_multiple_redirections(mini) == 1)
		return (1);
	return (0);
}

int	ft_split_input(t_mini *mini)
{
	mini->i = 0;
	mini->argc = 0;
	ft_count_arguments(mini);
	mini->i = 0;
	ft_handle_spaceflag(mini, 1);
	mini->args = malloc(sizeof(char *) * (mini->argc + 1));
	if (!mini->args)
	{
		ft_free_2d_arr(mini->env);
		free(mini->args);
		free(mini->space_flag);
		exit(EXIT_FAILURE);
	}
	if (ft_loop_input_string(mini) == 1)
	{
		ft_free_input(mini);
		return (1);
	}
	ft_redirections_change_position(mini);
	mini->args[mini->index] = NULL;
	return (0);
}

void	ft_count_arguments(t_mini *mini)
{
	while (mini->input[mini->i])
	{
		ft_skip_spaces(mini, mini->input);
		if (mini->input[mini->i] == '\0')
			break ;
		if (mini->input[mini->i] == '\'')
			ft_count_if_single_quote(mini);
		else if (mini->input[mini->i] == '"')
			ft_count_if_double_quote(mini);
		else if (mini->input[mini->i] == '<' || mini->input[mini->i] == '>')
			ft_count_if_redirections(mini, mini->input[mini->i]);
		else if (mini->input[mini->i] == '|')
			ft_count_if_pipes(mini);
		else
			ft_count_if_space(mini);
	}
}

int	ft_handle_spaceflag(t_mini *mini, int j)
{
	if (j == 1)
	{
		mini->space_flag = malloc(sizeof(int) * (mini->argc + 1));
		if (!mini->space_flag)
		{
			ft_free_2d_arr(mini->env);
			free(mini->space_flag);
			exit (1);
		}
	}
	else
	{
		if (mini->input[mini->i] == ' ')
			mini->space_flag[mini->index] = 1;
		else
			mini->space_flag[mini->index] = 0;
	}
	return (0);
}
