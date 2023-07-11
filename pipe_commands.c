/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:36:07 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/06 22:12:08 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_exec_external(t_mini *mini, char **args, char **envp)
{
	char	**dirs;
	char	*path_env;
	int		i;

	(void)envp;
	path_env = ft_get_value_from_env(mini->env, "PATH");
	if (path_env == NULL)
	{
		printf("minishell: %s: No such file or directory\n", args[0]);
		ft_free_when_forked(mini);
	}
	dirs = ft_split(path_env, ':');
	i = 0;
	ft_change_value(mini);
	ft_delete_quotes(mini);
	while (dirs[i])
	{
		if (ft_check_access_for_external(mini, i, dirs, args) == 1)
			exit(EXIT_FAILURE);
		i++;
	}
	ft_free_2d_arr(dirs);
	ft_command_not_found(mini, 1, 0);
	ft_free_when_forked(mini);
}

void	ft_execute_built_in_command(t_mini *mini, char **args)
{
	if (ft_strcmp_with_quotes(mini, args[0], "pwd") == 0)
	{
		ft_show_directory();
		ft_free_when_forked(mini);
	}
	else if (ft_strcmp_with_quotes(mini, args[0], "env") == 0)
	{
		ft_show_environment(mini);
		ft_free_when_forked(mini);
	}
	else if (ft_strcmp_with_quotes(mini, args[0], "echo") == 0)
	{
		ft_handle_echo(mini);
		ft_free_when_forked(mini);
	}
	else if (ft_strcmp_with_quotes(mini, args[0], "cd") == 0
		|| ft_strcmp_with_quotes(mini, args[0], "export") == 0
		|| ft_strcmp_with_quotes(mini, args[0], "exit") == 0
		|| ft_strcmp_with_quotes(mini, args[0], "unset") == 0)
		ft_free_when_forked(mini);
}
