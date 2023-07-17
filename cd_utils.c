/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:10:25 by ddyankov          #+#    #+#             */
/*   Updated: 2023/07/17 21:14:58 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
