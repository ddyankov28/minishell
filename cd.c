/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:11:40 by valentin          #+#    #+#             */
/*   Updated: 2023/07/14 12:41:45 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void ft_set_oldpwd(t_mini *mini, char *oldpwd)
{
    char	*name;
    char    *value;

	name = "OLDPWD";
    value = ft_strjoin("OLDPWD=", oldpwd);
	if (name != NULL && mini->value != NULL)
	{
		mini->env = ft_set_environment_variable(name, value,
				mini->env);
		free(value);
	}
}

static void ft_oldpwd(t_mini *mini)
{
    char *oldpwd;
    char    *current_path;

    current_path = ft_get_value_from_env(mini->env, "PWD");
    oldpwd = ft_get_value_from_env(mini->env, "OLDPWD");
    if (!oldpwd)
    {
        printf("minishell: cd: HOME not set\n");
        return ;
    }
    if (chdir(oldpwd) == 0)
        ft_set_oldpwd(mini, current_path);
    else
		perror("cd");
}

static void ft_home(t_mini *mini)
{
    char *home_dir;
    char    *current_path;

    current_path = ft_get_value_from_env(mini->env, "PWD");
    home_dir = ft_get_value_from_env(mini->env, "HOME");
    if (!home_dir)
    {
        printf("minishell: cd: HOME not set\n");
        return ;
    }
    if (chdir(home_dir) == 0)
        ft_set_oldpwd(mini, current_path);
    else
		perror("cd");
}

static void ft_change_to_cd(t_mini *mini)
{
    char	*path_env;
	char	**dirs;
	int		i;
    char    *current_path;

    current_path = ft_get_value_from_env(mini->env, "PWD");
	i = 0;
    path_env = ft_get_value_from_env(mini->env, "PATH");
	if (!path_env)
		perror("cd");
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
	char    *current_path;

    current_path = ft_get_value_from_env(mini->env, "PWD");
	mini->exit_value = 0;
	if (!mini->args[1] || (!ft_strcmp(mini->args[1], "~")))
        ft_change_to_cd(mini);
	else if (!ft_strcmp_with_quotes(mini, mini->args[1], "$PWD"))
		mini->exit_value = 0;
    else if (!ft_strcmp_with_quotes(mini, mini->args[1], "$HOME"))
        ft_home(mini);
    else if ((!ft_strcmp(mini->args[1], "-"))
        || !ft_strcmp_with_quotes(mini, mini->args[1], "$OLDPWD"))
        ft_oldpwd(mini);
	else if (chdir(mini->args[1]) == 0)
        ft_set_oldpwd(mini, current_path);
    else
	{
        write(1, "minishell: cd: ", 16);
        ft_command_not_found(mini, 0, 1);
        write(1, ": No such file or directory\n", 29);
        mini->exit_value = 1;
    }
}
