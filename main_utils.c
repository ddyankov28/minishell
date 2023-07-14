/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:42:46 by ddyankov          #+#    #+#             */
/*   Updated: 2023/07/14 12:33:56 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_copy_envp(t_mini *mini)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	mini->env = malloc(sizeof(char *) * (i + 1));
	if (!mini->env)
	{
		free(mini->env);
		printf("Environment Malloc Failed\n");
		exit(1);
	}
	i = 0;
	while (environ[i])
	{
		mini->env[i] = ft_strdup(environ[i]);
		i++;
	}
	mini->env[i] = NULL;
	mini->new_line = 0;
}

static void	ft_check_command(t_mini *mini)
{
	if ((!ft_strcmp(mini->args[0], "cat") && !mini->args[1])
		|| (!ft_strcmp(mini->args[0], "grep") && mini->args[1]))
		mini->new_line = 1;
}

static void	ft_fork_for_externals(t_mini *mini)
{
	pid_t	pid;
	int		status;

	pid = fork();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	{
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (!pid)
		{
			signal(SIGQUIT, handle_sigquit);
			signal(SIGINT, SIG_DFL);
			ft_search_and_execute(mini, 0);
			exit(0);
		}
		else
		{
			waitpid(pid, &status, 0);
			//printf("%d", status);
			ft_check_status(mini, status);
		}
	}
}

static void	ft_read_input(t_mini *mini)
{
	if (!mini->args[0])
		return ;
	ft_check_command(mini);
	if (!ft_check_for_redirection(mini))
		return ;
	if (ft_is_builtin(mini, mini->args[0]))
		ft_execute_built_ins(mini, mini->input);
	else
		ft_fork_for_externals(mini);
	ft_check_if_command(mini);
	ft_restore_and_close_fds(mini);
}

void	ft_handle_input(t_mini *mini)
{
	if (g_exit_status == 130)
		{
			mini->exit_value = 130;
			g_exit_status = 0;
		}
	if (!mini->args[0])
	{
		free(mini->args);
		free(mini->space_flag);
		return ;
	}
	if (mini->args[0][0] == '|')
	{
		ft_free_input(mini);
		printf("minishell: syntax error near unexpected token '|'\n");
		return ;
	}
	if (ft_check_if_pipe(mini->args))
		ft_execute_pipes(mini);
	else
	{
		ft_read_input(mini);
		ft_free_input(mini);
	}
}
