/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:47:03 by ddyankov          #+#    #+#             */
/*   Updated: 2023/07/13 13:13:05 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_show_directory(t_mini *mini)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		mini->exit_value = 0;
	}
	else
	{
		mini->exit_value = 1;
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
		mini->exit_value = 127;
		return ;
	}
	while (mini->env[i] != NULL)
	{
		printf("%s\n", mini->env[i]);
		i++;
	}
	mini->exit_value = 0;
}
