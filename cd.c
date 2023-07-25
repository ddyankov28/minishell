/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:11:40 by valentin          #+#    #+#             */
/*   Updated: 2023/07/24 12:21:58 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_set_oldpwd(t_mini *mini, char *oldpwd)
{
	char	*name;
	char	*value;

	name = "OLDPWD";
	value = ft_strjoin("OLDPWD=", oldpwd);
	if (value != NULL)
	{
		mini->env = ft_set_env_var(name, value, mini->env, mini);
		free(value);
	}
	ft_set_pwd(mini);
}

static void	ft_oldpwd(t_mini *mini, char *current_path)
{
	char	*oldpwd;

	oldpwd = ft_get_value_from_env(mini->env, "OLDPWD");
	if (!oldpwd)
		return ;
	if (chdir(oldpwd) == 0)
	{
		ft_set_oldpwd(mini, current_path);
		ft_show_directory(mini);
	}
	else
		perror("cd");
}

static void	ft_home(t_mini *mini, char *current_path)
{
	char	*home_dir;

	home_dir = ft_get_value_from_env(mini->env, "HOME");
	if (!home_dir)
	{
		printf("minishell: cd: HOME not set\n");
		mini->exit_value = 1;
		return ;
	}
	if (chdir(home_dir) == 0)
		ft_set_oldpwd(mini, current_path);
	else
		perror("cd");
}

static void	ft_change_to_cd(t_mini *mini, char *current_path)
{
	char	*path_env;
	char	**dirs;
	int		i;

	i = 0;
	path_env = ft_get_value_from_env(mini->env, "PATH");
	if (!path_env)
	{
		printf("minishell: cd: HOME not set\n");
		mini->exit_value = 1;
		return ;
	}
	dirs = ft_split(path_env, ':');
	while (dirs[0][i])
		i++;
	dirs[0][i - 3] = '\0';
	if (chdir(dirs[0]) == 0)
		ft_set_oldpwd(mini, current_path);
	else
		perror("cd");
	ft_free_2d_arr(dirs);
}

void	ft_change_directory(t_mini *mini)
{
	char	*current_path;

	current_path = ft_get_current_path(mini);
	mini->exit_value = 0;
	if (ft_check_arguments_num(mini, current_path) == 1)
		return ;
	else if (!mini->args[1] || (!ft_strcmp(mini->args[1], "~")))
		ft_change_to_cd(mini, current_path);
	else if (!ft_strcmp_with_quotes(mini, mini->args[1], "$PWD"))
		ft_pwd(mini);
	else if (!ft_strcmp_with_quotes(mini, mini->args[1], "$HOME"))
		ft_home(mini, current_path);
	else if ((!ft_strcmp(mini->args[1], "-")) || !ft_strcmp_with_quotes(mini,
			mini->args[1], "$OLDPWD"))
		ft_oldpwd(mini, current_path);
	else if (chdir(mini->args[1]) == 0)
		ft_set_oldpwd(mini, current_path);
	else
	{
		write(1, "minishell: cd: ", 16);
		ft_command_not_found(mini, 0, 1);
		write(1, ": No such file or directory\n", 29);
		mini->exit_value = 1;
	}
	free(current_path);
}
