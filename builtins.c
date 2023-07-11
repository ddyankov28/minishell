/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:47:03 by ddyankov          #+#    #+#             */
/*   Updated: 2023/06/29 14:11:15 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_change_directory_perror(t_mini *mini)
{
	write(1, "minishell: cd: ", 16);
	ft_command_not_found(mini, 0, 1);
	write(1, ": No such file or directory\n", 29);
	g_exit_status = 1;
}

void	ft_change_directory(t_mini *mini)
{
	char	*path_env;
	char	**dirs;
	int		i;

	i = 0;
	g_exit_status = 0;
	if (mini->args[1] == NULL || (ft_strcmp(mini->args[1], "~") == 0))
	{
		path_env = ft_get_value_from_env(mini->env, "PATH");
		if (path_env == NULL)
			perror("cd");
		dirs = ft_split(path_env, ':');
		while (dirs[0][i])
			i++;
		dirs[0][i - 3] = '\0';
		if (chdir(dirs[0]) != 0)
			perror("cd");
		ft_free_2d_arr(dirs);
	}
	else if (ft_strcmp_with_quotes(mini, mini->args[1], "$PWD") == 0)
		g_exit_status = 0;
	else if (chdir(mini->args[1]) != 0)
		ft_change_directory_perror(mini);
}

void	ft_show_directory(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		g_exit_status = 0;
	}
	else
	{
		g_exit_status = 1;
		perror("getcwd() error");
	}
}

void	ft_show_environment(t_mini *mini)
{
	int		i;
	char	*path_env;

	i = 0;
	path_env = ft_get_value_from_env(mini->env, "PATH");
	if (!path_env)
	{
		printf("minishell: env: No such file or directory\n");
		return ;
	}
	if (mini->args[1] != NULL)
	{
		printf("env: '%s': No such file or directory\n", mini->args[1]);
		g_exit_status = 127;
		return ;
	}
	while (mini->env[i] != NULL)
	{
		printf("%s\n", mini->env[i]);
		i++;
	}
	g_exit_status = 0;
}
