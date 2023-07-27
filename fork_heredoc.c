/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:19:15 by ddyankov          #+#    #+#             */
/*   Updated: 2023/07/27 12:55:16 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_heredoc_loop(t_mini *mini, char *inp_line, char *delim)
{
	int		j;
	char	*new_delim;
	char	*str;

	j = 0;
	new_delim = ft_new_str(mini, delim);
	while (1)
	{
		inp_line = readline("> ");
		if (!inp_line)
			break ;
		if (!ft_strncmp(inp_line, new_delim, ft_strlen(new_delim))
			&& (inp_line[ft_strlen(new_delim)] == '\n'
				|| inp_line[ft_strlen(new_delim)] == '\0'))
		{
			ft_putstr_fd(NULL, mini->input_fd);
			break ;
		}
		str = ft_replace_line(inp_line, mini);
		ft_putendl_fd(str, mini->input_fd);
		j++;
		free(inp_line);
		free(str);
	}
	free(inp_line);
}

static void	ft_heredoc_child(t_mini *mini, char *inp_line, char *delim)
{
	int	i;

	i = 0;
	signal(SIGQUIT, handle_sigquit);
	signal(SIGINT, SIG_DFL);
	ft_heredoc_loop(mini, inp_line, delim);
	ft_free_2d_arr(mini->exec_arr);
	free(delim);
	free(mini->space_flag);
	ft_free_2d_arr(mini->env);
	while (i < mini->index)
	{
		free(mini->args[i]);
		i++;
	}
	free(mini->args);
	free(mini->input);
}

void	ft_fork_heredoc(t_mini *mini, char *inp_line, char *delimiter)
{
	int		status;
	pid_t	pid;

	pid = fork();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pid == -1)
		ft_fork_error();
	else if (!pid)
	{
		ft_heredoc_child(mini, inp_line, delimiter);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (status == 2)
		{
			mini->exit_value = 130;
			g_exit_status = 130;
			write(1, "\n", 1);
		}
	}
}
