/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:10:25 by ddyankov          #+#    #+#             */
/*   Updated: 2023/07/22 14:03:25 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_set_pwd(t_mini *mini)
{
	char	*current_path;
	char	*name;
	char	*value;

	name = "PWD";
	current_path = ft_get_current_path(mini);
	value = ft_strjoin("PWD=", current_path);
	free(current_path);
	if (value != NULL)
	{
		mini->env = ft_set_env_var(name, value, mini->env, mini);
		free(value);
	}
}

char	*ft_get_current_path(t_mini *mini)
{
	char	*path;

	path = malloc(sizeof(char) * 1024);
	if (!path)
		ft_free_malloc(mini);
	if (getcwd(path, 1024) == NULL)
	{
		perror("getcwd() error");
		free(path);
		return (NULL);
	}
	return (path);
}

int	ft_check_arguments_num(t_mini *mini, char *current_path)
{
	int	num;

	num = 0;
	while (mini->args[num])
		num++;
	if (num > 2)
	{
		printf("minishell: cd: too many arguments\n");
		free(current_path);
		mini->exit_value = 1;
		return (1);
	}
	return (0);
}
