/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:46:53 by ddyankov          #+#    #+#             */
/*   Updated: 2023/07/31 15:00:32 by vstockma         ###   ########.fr       */
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
		ft_show_directory(mini);
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

void	ft_yes_directory(t_mini *mini)
{
	DIR	*dir;

	dir = opendir(mini->args[0]);
	if (dir != NULL)
	{
		printf("minishell: %s: Is a directoy\n", mini->args[0]);
		ft_free_2d_arr(mini->env);
		ft_free_input(mini);
		closedir(dir);
		exit(126);
	}
	else
	{
		closedir(dir);
		execve(mini->args[0], mini->args, mini->env);
		ft_free_2d_arr(mini->env);
		ft_free_input(mini);
		exit(1);
	}
}

int	ft_question(t_mini *mini)
{
	char	*str;
	int		xyz;

	xyz = 0;
	if (mini->args[mini->xx][mini->j] == '?')
	{
		mini->j++;
		str = ft_itoa(mini->exit_value);
		while (str[xyz])
			mini->new_str[mini->in++] = str[xyz++];
		free(str);
		free(mini->str_to_look);
		return (0);
	}
	return (1);
}

void	ft_allocate_and_initiate(t_mini *mini)
{
	mini->a = 0;
	mini->str_to_look = ft_calloc(1024, 1);
	mini->j++;
	mini->env_index = 0;
}
