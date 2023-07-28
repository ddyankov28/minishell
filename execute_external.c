/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:47:41 by ddyankov          #+#    #+#             */
/*   Updated: 2023/07/28 11:55:45 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_search_and_execute(t_mini *mini, int sw)
{
	char	*path_env;
	char	**dirs;
	int		i;

	path_env = ft_get_value_from_env(mini->env, "PATH");
	ft_check_path(mini, path_env, sw);
	dirs = ft_split(path_env, ':');
	i = 0;
	ft_change_value(mini);
	while (dirs[i])
	{
		if (ft_check_access_for_external(mini, i, dirs, mini->args) == 1)
			exit(EXIT_SUCCESS);
		i++;
	}
	ft_free_2d_arr(dirs);
	ft_command_not_found(mini, 1, 0);
	if (sw == 0)
	{
		ft_free_2d_arr(mini->env);
		ft_free_input(mini);
	}
	else
		ft_free_when_forked(mini);
}

int	ft_check_access_for_external(t_mini *mini, int i, char **dirs, char **args)
{
	char	*dir_path;
	char	*path;

	if (mini->is_redirection != 0)
		ft_delete_quotes_for_str(mini, 0);
	dir_path = ft_strjoin(dirs[i], "/");
	path = ft_strjoin(dir_path, args[0]);
	free(dir_path);
	if (access(path, F_OK | X_OK) == 0)
	{
		ft_execute_external(path, mini, args, dirs);
		free(path);
		ft_free_2d_arr(dirs);
		return (1);
	}
	free(path);
	return (0);
}

void	ft_exit_if_no_path(t_mini *mini)
{
	if (mini->input[0] != '$')
	{
		write(1, "minishell: ", 11);
		ft_command_not_found(mini, 0, 0);
		printf(": No such file or directory\n");
	}
	ft_free_2d_arr(mini->env);
	ft_free_input(mini);
	exit(127);
}

int	ft_change_value(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->args[i])
	{
		if (ft_strcmp(mini->args[i], "$?") == 0 || ft_strcmp(mini->args[i],
				"\"$?\"") == 0)
		{
			free(mini->args[i]);
			mini->args[i] = ft_itoa(mini->exit_value);
		}
		i++;
	}
	return (0);
}

void	ft_execute_external(char *path, t_mini *mini, char **args, char **dirs)
{
	if (execve(path, args, mini->env) == -1)
	{
		ft_free_2d_arr(mini->env);
		ft_free_2d_arr(mini->args);
		ft_free_2d_arr(dirs);
		free(mini->space_flag);
		free(path);
		perror("execve error");
		exit(EXIT_FAILURE);
	}
}
