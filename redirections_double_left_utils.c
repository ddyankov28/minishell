/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_double_left_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:35:19 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/27 16:51:25 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	ft_after_dollar(t_mini *mini, int i, char *s, char *output)
{
	char	*var_name;
	char	*value;
	int		start;
	int		end;

	start = i + 1;
	end = i + 1;
	while (s[end])
	{
		if (s[end] == '$' || ft_isspace(s[end]) || s[end] == '\n')
			break ;
		end++;
		i++;
	}
	var_name = ft_substr(s, start, end - start);
	value = ft_get_value_from_env(mini->env, var_name);
	if (value)
	{
		ft_strncpy(output + mini->output_len, value, ft_strlen(value));
		mini->output_len += ft_strlen(value);
		free(var_name);
	}
	else
		free(var_name);
	return (i);
}

char	*ft_replace_line(char *s, t_mini *mini)
{
	char	*output;
	int		i;

	mini->output_len = 0;
	i = 0;
	output = malloc(1024 * sizeof(char));
	if (!output)
		ft_free_malloc(mini);
	while (s[i])
	{
		if (s[i] == '$')
			i = ft_after_dollar(mini, i, s, output);
		else if (s[i] == '\0' || s[i] == '\n')
			break ;
		else
		{
			output[mini->output_len] = s[i];
			mini->output_len++;
		}
		i++;
	}
	output[mini->output_len] = '\0';
	return (output);
}

static void	ft_heredoc_loop(t_mini *mini, char *inp_line, char *delim)
{
	char	*new_delim;
	char	*str;

	new_delim = ft_new_str(mini, delim);
	while (g_exit_status != 130)
	{
		ft_putstr_fd("> ", 1);
		inp_line = get_next_line(0);
		if (!inp_line)
			break ;
		if (!ft_strncmp(inp_line, new_delim, ft_strlen(new_delim))
			&& (inp_line[ft_strlen(new_delim)] == '\n'
				|| inp_line[ft_strlen(new_delim)] == '\0'))
		{
			ft_putstr_fd(NULL, mini->input_fd);
			free(inp_line);
			break ;
		}
		str = ft_replace_line(inp_line, mini);
		ft_putendl_fd(str, mini->input_fd);
		free(inp_line);
		free(str);
	}
	
}

int	ft_read_input_redirection(t_mini *mini, int i)
{
	char	*input_line;
	char	*delimiter;

	delimiter = ft_strdup(mini->args[i + 1]);
	input_line = NULL;
	signal(SIGINT, sigint_heredoc);
	ft_heredoc_loop(mini, input_line, delimiter);
	free(delimiter);
	if (i == 0)
		return (1);
	if (g_exit_status == 130)
	{
		unlink("/tmp/mini_here_doc_XXXXXX");
		return (1);
	}
	return (0);
}
