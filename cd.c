/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:11:40 by valentin          #+#    #+#             */
/*   Updated: 2023/07/17 16:07:26 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char* ft_get_current_path(t_mini *mini)
{
    char* path = malloc(sizeof(char) * 1024);
    if (path == NULL)
        ft_free_malloc(mini);   
    if (getcwd(path, 1024) == NULL)
    {
        perror("getcwd() error");
        free(path);
        return NULL;
    }
    return (path);
}

static void ft_set_oldpwd(t_mini *mini, char *oldpwd)
{
    char	*name;
    char    *value;

	name = "OLDPWD";
    value = ft_strjoin("OLDPWD=", oldpwd);
	if (value != NULL)
	{
		mini->env = ft_set_environment_variable(name, value,
				mini->env);
		free(value);
	}
}

static void ft_oldpwd(t_mini *mini, char *current_path)
{
    char *oldpwd;

    oldpwd = ft_get_value_from_env(mini->env, "OLDPWD");
    if (!oldpwd)
    {
        printf("minishell: cd: HOME not set\n");
        return ;
    }
    if (chdir(oldpwd) == 0)
    {
        ft_set_oldpwd(mini, current_path);
        ft_show_directory(mini);
    }
    else
		perror("cd");
}

static void ft_home(t_mini *mini, char *current_path)
{
    char *home_dir;

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

static void ft_change_to_cd(t_mini *mini, char *current_path)
{
    char	*path_env;
	char	**dirs;
	int		i;

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

int     ft_check_arguments_num(t_mini *mini, char *current_path)
{
    int     num;

    num = 0;
    while (mini->args[num])
        num++;
    if(num > 2)
    {
        printf("minishell: cd: too many arguments\n");
        free(current_path);
        mini->exit_value = 1;
        return (1);
    }
    return (0);
}

void	ft_change_directory(t_mini *mini)
{
	char    *current_path;

    current_path = ft_get_current_path(mini);
	mini->exit_value = 0;
    if (ft_check_arguments_num(mini, current_path) == 1)
        return ;
	else if (!mini->args[1] || (!ft_strcmp(mini->args[1], "~")))
        ft_change_to_cd(mini, current_path);
	else if (!ft_strcmp_with_quotes(mini, mini->args[1], "$PWD"))
		mini->exit_value = 0;
    else if (!ft_strcmp_with_quotes(mini, mini->args[1], "$HOME"))
        ft_home(mini, current_path);
    else if ((!ft_strcmp(mini->args[1], "-"))
        || !ft_strcmp_with_quotes(mini, mini->args[1], "$OLDPWD"))
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
