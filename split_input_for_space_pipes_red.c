/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input_for_space_pipes_red.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:00:08 by vstockma          #+#    #+#             */
/*   Updated: 2023/08/01 11:06:59 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_split_space(t_mini *mini)
{
	int	j;

	j = 0;
	mini->args[mini->index] = malloc(sizeof(char) * 1024);
	if (!mini->args[mini->index])
		ft_free_malloc(mini);
	while (mini->input[mini->i])
	{
		if (mini->input[mini->i] == ' ' || mini->input[mini->i] == '<'
			|| mini->input[mini->i] == '>' || mini->input[mini->i] == '|')
			break ;
		else if (mini->input[mini->i] == '\'' || mini->input[mini->i] == '"')
		{
			if (ft_put_in_args_extension(mini) == 1)
				break ;
		}
		mini->args[mini->index][j++] = mini->input[mini->i++];
	}
	mini->args[mini->index][j] = '\0';
	ft_handle_spaceflag(mini, 2);
	mini->index++;
}

int	ft_put_in_args_extension(t_mini *mini)
{
	ft_look_for_pair(mini);
	if (mini->flag_for_pair == 1)
	{
		mini->flag_for_pair = 0;
		return (1);
	}
	return (0);
}

int	ft_split_redirections(t_mini *mini, char c)
{
	int	j;

	j = 0;
	mini->args[mini->index] = malloc(ft_get_len_for_char(mini->input, c,
				mini->i) + 1);
	if (!mini->args[mini->index])
		ft_free_malloc(mini);
	if (c == '<')
	{
		while (mini->input[mini->i] == '<')
			mini->args[mini->index][j++] = mini->input[mini->i++];
		mini->redirection_count = j;
	}
	else
	{
		while (mini->input[mini->i] == '>')
			mini->args[mini->index][j++] = mini->input[mini->i++];
		mini->redirection_count = j;
	}
	mini->args[mini->index][j] = '\0';
	ft_handle_spaceflag(mini, 2);
	mini->index++;
	if (ft_unexpected(mini) == 1)
		return (1);
	return (0);
}

int	ft_split_pipes(t_mini *mini)
{
	int	j;

	j = 0;
	mini->args[mini->index] = malloc(ft_get_len_for_char(mini->input, '|',
				mini->i) + 1);
	if (!mini->args[mini->index])
	{
		free(mini->args[mini->index]);
		ft_free_malloc(mini);
	}
	while (mini->input[mini->i] == '|')
		mini->args[mini->index][j++] = mini->input[mini->i++];
	mini->args[mini->index][j] = '\0';
	ft_handle_spaceflag(mini, 2);
	mini->index++;
	ft_skip_spaces(mini, mini->input);
	if (mini->input[mini->i] == '\0')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		mini->exit_value = 2;
		return (1);
	}
	return (0);
}

void	ft_skip_dollar(t_mini *mini)
{
	if (mini->args[mini->xx + 1] != NULL)
	{
		if (ft_strcmp(mini->args[mini->xx], "$") == 0
			&& mini->space_flag[mini->xx] == 0)
		{
			mini->xx++;
			mini->z++;
		}
	}
}
