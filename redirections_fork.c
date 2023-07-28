/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_fork.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 12:12:53 by ddyankov          #+#    #+#             */
/*   Updated: 2023/07/27 19:24:31 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_free_heredoc(t_mini *mini)
{
	ft_free_2d_arr(mini->exec_arr);
	unlink("/tmp/mini_here_doc_XXXXXX");
}

void	ft_no_path(t_mini *mini)
{
	ft_free_input(mini);
	ft_free_2d_arr(mini->env);
	exit(1);
}

void	ft_execve_error(t_mini *mini)
{
	ft_free_input(mini);
	ft_free_2d_arr(mini->env);
	unlink("/tmp/mini_here_doc_XXXXXX");
	exit(1);
}

void	ft_not_valid(t_mini *mini)
{
	ft_printf("minishell: export: `");
	ft_write_without_quotes(mini, mini->args[mini->not_valid]);
	ft_printf("': not a valid identifier\n");
	mini->exit_value = 1;
	free(mini->name);
	if (mini->value)
		free(mini->value);
}

void	ft_pwd(t_mini *mini)
{
	char	*pwd_dir;

	pwd_dir = ft_get_value_from_env(mini->env, "PWD");
	if (!pwd_dir)
	{
		printf("minishell: cd: HOME not set\n");
		mini->exit_value = 1;
		return ;
	}
	mini->exit_value = 0;
}
