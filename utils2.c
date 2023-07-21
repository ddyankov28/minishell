/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:56:22 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/21 13:41:52 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_command_not_found_loop(t_mini *mini, int i)
{
	mini->fd = STDERR_FILENO;
	while (mini->args[i])
	{
		mini->space_or_not = 1;
		if (mini->args[i][0] == '\"' && ft_look_for_quote(mini, mini->args[i],
			0) == 1)
			ft_echo_double(mini, mini->args[i], 0);
		else if (mini->args[i][0] == '\'' && ft_look_for_quote(mini,
			mini->args[i], 0))
			ft_echo_single(mini, mini->args[i], 0);
		else
			ft_echo_unclosed(mini, mini->args[i], 0);
		if (mini->space_flag[i] != 0)
			break ;
		i++;
	}
}

void	ft_command_not_found(t_mini *mini, int sw, int i)
{
	char	*env_val;
	char	*to_compare;

	ft_command_not_found_loop(mini, i);
	if (sw == 1)
	{
		if (mini->args[0][0] == '$' && mini->args[1] == NULL)
		{
			to_compare = ft_strtrim(mini->args[0], "$");
			env_val = ft_get_value_from_env(mini->env, to_compare);
			free(to_compare);
			if (!env_val)
			{
				mini->exit_value = 0;
				return ;
			}
		}
		ft_putendl_fd(": command not found", mini->fd);
		mini->exit_value = 127;
	}
	mini->fd = 1;
	return ;
}

static void	ft_check_path_if(t_mini *mini, char *path_env, int sw)
{
	if (access(mini->args[0], F_OK | X_OK) == 0)
	{
		execve(mini->args[0], mini->args, mini->env);
		exit(1);
	}
	if (!path_env && sw == 0)
		ft_exit_if_no_path(mini);
	else if (!path_env && sw == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(mini->args[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
		ft_free_when_forked(mini);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(mini->args[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
		ft_free_2d_arr(mini->args);
		ft_free_2d_arr(mini->env);
		free(mini->space_flag);
		exit(2);
	}
}

static void	ft_help_me(t_mini *mini, char *path_env, int sw)
{
	if (!path_env && sw == 0)
		ft_exit_if_no_path(mini);
	else if (!path_env && sw == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(mini->args[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
		ft_free_when_forked(mini);
	}
}

void	ft_check_path(t_mini *mini, char *path_env, int sw)
{
	int	file_exists;

	file_exists = 0;
	ft_delete_quotes_for_str(mini, 0);
	file_exists = open(mini->args[0], O_RDONLY);
	if (ft_strchr(mini->args[0], '/') != NULL)
	{
		if (file_exists != -1 || errno == EACCES || errno == EPERM)
		{
			close(file_exists);
			if (access(mini->args[0], F_OK | X_OK) == 0)
			{
				execve(mini->args[0], mini->args, mini->env);
				exit(0);
			}
			printf("minishell: %s: Permission denied\n", mini->args[0]);
			exit(126);
		}
		else
			ft_check_path_if(mini, path_env, sw);
	}
	else
		ft_help_me(mini, path_env, sw);
}
