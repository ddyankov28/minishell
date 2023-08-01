/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:36:07 by vstockma          #+#    #+#             */
/*   Updated: 2023/08/01 11:11:25 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_execute_built_in_command(t_mini *mini, char **args)
{
	if (ft_strcmp_with_quotes(mini, args[0], "pwd") == 0)
	{
		ft_show_directory(mini);
		ft_free_when_forked(mini);
	}
	else if (ft_strcmp_with_quotes(mini, args[0], "env") == 0)
	{
		ft_show_environment(mini);
		ft_free_when_forked(mini);
	}
	else if (ft_strcmp_with_quotes(mini, args[0], "echo") == 0)
	{
		ft_handle_echo(mini);
		ft_free_when_forked(mini);
	}
	else if (ft_strcmp_with_quotes(mini, args[0], "cd") == 0
		|| ft_strcmp_with_quotes(mini, args[0], "export") == 0
		|| ft_strcmp_with_quotes(mini, args[0], "exit") == 0
		|| ft_strcmp_with_quotes(mini, args[0], "unset") == 0)
		ft_free_when_forked(mini);
}

int	ft_check_mini_arg(t_mini *mini, char *s)
{
	if (!s)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		mini->exit_value = 2;
		return (0);
	}
	return (1);
}
