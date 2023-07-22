/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:47:03 by ddyankov          #+#    #+#             */
/*   Updated: 2023/07/22 11:47:30 by ddyankov         ###   ########.fr       */
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

	i = 0;
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
