/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:11:35 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/28 14:02:57 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_check_if_command(t_mini *mini)
{
	if (ft_is_builtin(mini, mini->args[0]))
		return (0);
	else
	{
		if (ft_check_if_external(mini) == 0)
			return (0);
	}
	return (1);
}

int	ft_check_if_external(t_mini *mini)
{
	char	*path_env;
	char	**dirs;
	int		i;

	path_env = ft_get_value_from_env(mini->env, "PATH");
	if (!path_env)
		return (1);
	dirs = ft_split(path_env, ':');
	i = 0;
	while (dirs[i])
	{
		if (ft_check_if_access(mini, i, dirs, mini->args) == 1)
			return (0);
		i++;
	}
	ft_free_2d_arr(dirs);
	if (mini->exit_value == 126)
		mini->exit_value = 126;
	else if (mini->exit_value == 0)
		mini->exit_value = 0;
	else
		mini->exit_value = 127;
	return (1);
}

static void	ft_blabla(int x, char *path, char **dirs, char *str)
{
	if (x == 1)
		free(path);
	ft_free_2d_arr(dirs);
	free(str);
}

int	ft_check_if_access(t_mini *mini, int i, char **dirs, char **args)
{
	int		x;
	char	*dir_path;
	char	*path;
	char	*str;

	str = ft_strdup(args[0]);
	x = 0;
	str = ft_remove_quotes(mini, str);
	dir_path = ft_strjoin(dirs[i], "/");
	if (ft_strchr(str, '/') != NULL)
		path = str;
	else
	{
		path = ft_strjoin(dir_path, str);
		x = 1;
	}
	free(dir_path);
	if (access(path, F_OK | X_OK) == 0)
	{
		ft_blabla(x, path, dirs, str);
		return (1);
	}
	if (x == 1)
		free(path);
	return (free(str), 0);
}

int	ft_exit_out(t_mini *mini)
{
	if (mini->args[0] == 0)
	{
		mini->exit_value = 0;
		return (1);
	}
	return (0);
}
