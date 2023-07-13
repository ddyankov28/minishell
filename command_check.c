/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:11:35 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/13 12:25:26 by valentin         ###   ########.fr       */
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
	ft_delete_quotes(mini);
	while (dirs[i])
	{
		if (ft_check_if_access(i, dirs, mini->args) == 1)
			return (0);
		i++;
	}
	ft_free_2d_arr(dirs);
	mini->exit_value = 127;
	return (1);
}

int	ft_check_if_access(int i, char **dirs, char **args)
{
	int		x;
	char	*dir_path;
	char	*path;

	x = 0;
	dir_path = ft_strjoin(dirs[i], "/");
	if (ft_strchr(args[0], '/') != NULL)
		path = args[0];
	else
	{
		path = ft_strjoin(dir_path, args[0]);
		x = 1;
	}
	free(dir_path);
	if (access(path, F_OK | X_OK) == 0)
	{
		if (x == 1)
			free(path);
		ft_free_2d_arr(dirs);
		return (1);
	}
	if (x == 1)
		free(path);
	return (0);
}
