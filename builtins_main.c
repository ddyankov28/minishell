/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:46:53 by ddyankov          #+#    #+#             */
/*   Updated: 2023/06/28 15:26:56 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_execute_built_ins(t_mini *mini, char *input)
{
	if (ft_strcmp_with_quotes(mini, mini->args[0], "exit") == 0)
		ft_exit(input, mini);
	else if (ft_strcmp_with_quotes(mini, mini->args[0], "cd") == 0)
		ft_change_directory(mini);
	else if (ft_strcmp_with_quotes(mini, mini->args[0], "pwd") == 0)
		ft_show_directory();
	else if (ft_strcmp_with_quotes(mini, mini->args[0], "env") == 0)
		ft_show_environment(mini);
	else if (ft_strcmp_with_quotes(mini, mini->args[0], "echo") == 0)
		ft_handle_echo(mini);
	else if (ft_strcmp_with_quotes(mini, mini->args[0], "unset") == 0)
		mini->env = ft_unset_environment_variable(mini);
	else if (ft_strcmp_with_quotes(mini, mini->args[0], "export") == 0)
		ft_handle_export(mini);
}

int	ft_is_builtin(t_mini *mini, char *command)
{
	if (ft_strcmp_with_quotes(mini, command, "cd") == 0
		|| ft_strcmp_with_quotes(mini, command, "echo") == 0
		|| ft_strcmp_with_quotes(mini, command, "env") == 0
		|| ft_strcmp_with_quotes(mini, command, "exit") == 0
		|| ft_strcmp_with_quotes(mini, command, "pwd") == 0
		|| ft_strcmp_with_quotes(mini, command, "unset") == 0
		|| ft_strcmp_with_quotes(mini, command, "export") == 0)
	{
		return (1);
	}
	return (0);
}
