/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:26:24 by vstockma          #+#    #+#             */
/*   Updated: 2023/08/01 11:10:10 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_split_into_commands(t_mini *mini)
{
	int		i;
	int		index;
	char	*command;

	index = 0;
	i = 0;
	command = NULL;
	mini->commands = ft_calloc(sizeof(char *), 1024);
	ft_help_split_commands(mini, i, index, command);
	ft_free_input(mini);
}

void	ft_help_split_commands(t_mini *mini, int i, int index, char *command)
{
	while (mini->args[i])
	{
		if (mini->args[i][0] == '|')
		{
			mini->commands[index] = ft_strdup(command);
			free(command);
			i++;
			index++;
		}
		command = ft_calloc(1, 1024);
		while (mini->args[i])
		{
			if (mini->args[i][0] == '|')
				break ;
			ft_strcat(command, mini->args[i]);
			if (mini->space_flag[i] == 1)
				ft_strcat(command, " ");
			i++;
		}
	}
	mini->commands[index] = ft_strdup(command);
	free(command);
	index++;
	mini->commands[index] = NULL;
}

void	ft_write_quotes(t_mini *mini)
{
	if (mini->args[mini->xx][mini->j] == '\0' && mini->space_flag[mini->xx
		- 1] == 1)
	{
		mini->new_str[mini->in++] = '\'';
		mini->new_str[mini->in++] = '\'';
	}
}

int	ft_unexpected(t_mini *mini)
{
	ft_skip_spaces(mini, mini->input);
	if (mini->input[mini->i] == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		mini->exit_value = 2;
		return (1);
	}
	return (0);
}

int	ft_loop_more_strings(t_mini *mini)
{
	if (mini->input[mini->i] == '|')
	{
		if (ft_split_pipes(mini) == 1)
			return (1);
	}
	else
		ft_split_space(mini);
	return (0);
}
