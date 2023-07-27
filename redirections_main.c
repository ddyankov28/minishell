/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:51:25 by ddyankov          #+#    #+#             */
/*   Updated: 2023/07/27 16:18:01 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_expand_str(t_mini *mini, int i)
{
	int		j;
	char	*env_var;
	char	*str_to_look;
	int		index;

	index = 0;
	j = 0;
	ft_delete_quotes_for_str(mini, i);
	if (mini->args[i][j] == '$')
	{
		str_to_look = ft_calloc(1024, 1);
		j++;
		while (ft_isalpha(mini->args[i][j]) && mini->args[i][j])
		{
			str_to_look[index++] = mini->args[i][j++];
		}
		env_var = ft_get_value_from_env(mini->env, str_to_look);
		free(str_to_look);
		if (!env_var)
		{
			printf("minishell: %s: ambiguous redirect\n", mini->args[i]);
			return (1);
		}
		free(mini->args[i]);
		mini->args[i] = ft_strdup(env_var);
	}
	mini->is_redirection = 1;
	return (0);
}

static int	ft_double_redirect_left(t_mini *mini, int i)
{
	mini->exec_arr = malloc(1024 * sizeof(char *));
	if (!mini->exec_arr)
	{
		free(mini->exec_arr);
		ft_free_malloc(mini);
	}
	if (ft_expand_str(mini, i + 1) == 1)
		return (1);
	mini->exec_arr[0] = ft_strdup(mini->args[0]);
	mini->exec_arr[1] = ft_strdup("/tmp/mini_here_doc_XXXXXX");
	mini->exec_arr[2] = NULL;
	mini->here++;
	if (!ft_check_mini_arg(mini->args[i + 1]))
		return (1);
	free(mini->args[i]);
	mini->args[i] = NULL;
	mini->input_fd = open("/tmp/mini_here_doc_XXXXXX",
			O_CREAT | O_EXCL | O_RDWR, 0777);
	if (mini->input_fd < 0)
		ft_input_fd(mini);
	if (ft_read_input_redirection(mini, i) == 1)
		return (1);
	if (mini->here != mini->count_heredoc)
		unlink("/tmp/mini_here_doc_XXXXXX");
	return (0);
}

static int	ft_double_redirect_right(t_mini *mini, int i)
{
	if (!ft_check_mini_arg(mini->args[i + 1]))
		return (1);
	if (ft_expand_str(mini, i + 1) == 1)
		return (1);
	free(mini->args[i]);
	mini->args[i] = NULL;
	ft_delete_quotes_for_str(mini, i + 1);
	mini->append_fd = open(mini->args[i + 1], O_CREAT | O_WRONLY | O_APPEND,
			0777);
	if (i == 0)
		return (1);
	if (mini->append_fd == -1)
	{
		perror("Append file error");
		mini->exit_value = 1;
		return (1);
	}
	if (ft_redirect_right_check(mini))
		return (1);
	if (mini->append_fd != -1)
	{
		mini->stdout_copy = dup(STDOUT_FILENO);
		dup2(mini->append_fd, STDOUT_FILENO);
		close(mini->append_fd);
	}
	return (0);
}

static int	ft_redirect_right(t_mini *mini, int i)
{
	if (!ft_check_mini_arg(mini->args[i + 1]))
		return (1);
	if (ft_expand_str(mini, i + 1) == 1)
		return (1);
	free(mini->args[i]);
	mini->args[i] = NULL;
	ft_delete_quotes_for_str(mini, i + 1);
	mini->output_fd = open(mini->args[i + 1], O_CREAT | O_WRONLY | O_TRUNC,
			0777);
	if (i == 0)
		return (1);
	if (mini->output_fd < 0)
	{
		perror("open output file");
		mini->exit_value = 1;
		return (1);
	}
	if (ft_redirect_right_check(mini))
		return (1);
	if (mini->output_fd != -1)
	{
		mini->stdout_copy = dup(STDOUT_FILENO);
		dup2(mini->output_fd, STDOUT_FILENO);
		close(mini->output_fd);
	}
	return (0);
}

static int	ft_redirect_left(t_mini *mini, int i)
{
	if (!ft_check_mini_arg(mini->args[i + 1]))
		return (1);
	if (ft_expand_str(mini, i + 1) == 1)
		return (1);
	free(mini->args[i]);
	mini->args[i] = NULL;
	ft_delete_quotes_for_str(mini, i + 1);
	mini->input_fd = open(mini->args[i + 1], O_RDONLY);
	if (i == 0)
		return (1);
	if (mini->input_fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_command_not_found(mini, 0, i + 1);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		mini->exit_value = 1;
		return (1);
	}
	return (0);
}

int	ft_check_for_redirection(t_mini *mini)
{
	int	i;
	int	return_val;

	return_val = 0;
	i = 0;
	ft_count_double_left(mini);
	while (mini->args[i])
	{
		if (!ft_strcmp(mini->args[i], "<"))
			return_val = ft_redirect_left(mini, i);
		else if (!ft_strcmp(mini->args[i], ">"))
			return_val = ft_redirect_right(mini, i);
		else if (!ft_strcmp(mini->args[i], ">>"))
			return_val = ft_double_redirect_right(mini, i);
		else if (!ft_strcmp(mini->args[i], "<<"))
			return_val = ft_double_redirect_left(mini, i);
		i++;
		if (return_val == 1)
			return (0);
	}
	ft_apply_input_redirections(mini);
	return (1);
}
