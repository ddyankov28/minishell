/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:42:46 by ddyankov          #+#    #+#             */
/*   Updated: 2023/08/01 11:06:16 by vstockma         ###   ########.fr       */
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
}

static void	ft_fork_for_externals(t_mini *mini)
{
	pid_t	pid;
	int		status;

	pid = fork();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pid == -1)
		ft_fork_error();
	else if (!pid)
	{
		signal(SIGQUIT, handle_sigquit);
		signal(SIGINT, SIG_DFL);
		ft_search_and_execute(mini, 0);
		if (mini->exit_value == 127)
			exit(127);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		ft_check_status(mini, status);
	}
}

int	ft_is_dircetory(t_mini *mini)
{
	char	*env_value;
	char	*to_compare;

	ft_delete_quotes_for_str(mini, 0);
	if (ft_check_folder(mini) == 0)
		env_value = mini->args[0];
	else
	{
		if (mini->args[0][0] != '$')
			return (0);
		to_compare = ft_strtrim(mini->args[0], "$");
		env_value = ft_get_value_from_env(mini->env, to_compare);
		free(to_compare);
	}
	if (!env_value)
	{
		mini->exit_value = 0;
		return (1);
	}
	if (access(env_value, F_OK | X_OK) == 0)
	{
		mini->exit_value = 126;
		return (printf("minishell: %s: Is a directoy\n", env_value), 1);
	}
	return (0);
}

static void	ft_read_input(t_mini *mini)
{
	if (!mini->args[0])
		return ;
	if (!ft_strcmp_with_quotes(mini, mini->args[0], "$PWD")
		|| !ft_strcmp_with_quotes(mini, mini->args[0], "$HOME")
		|| !ft_strcmp_with_quotes(mini, mini->args[0], "$OLDPWD")
		|| ft_strchr(mini->args[0], '/') != NULL)
	{
		if (ft_is_dircetory(mini) == 1)
			return ;
	}
	if (!ft_check_for_redirection(mini))
		return ;
	if (mini->here > 0)
		ft_fork_redirections(mini);
	if (mini->is_redirection == 0)
		ft_expand(mini);
	if (ft_exit_out(mini) == 1)
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
	if (ft_check_if_pipe(mini->args) == 1)
		ft_execute_pipes(mini);
	else if (ft_check_if_pipe(mini->args) == 2)
	{
		ft_free_input(mini);
		printf("minishell: syntax error near unexpected token `|'\n");
		mini->exit_value = 2;
		return ;
	}
	else
	{
		ft_read_input(mini);
		ft_free_input(mini);
	}
}
