/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:26:24 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/28 11:20:01 by vstockma         ###   ########.fr       */
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
