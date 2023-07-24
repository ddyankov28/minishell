/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_double_left_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:35:19 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/24 11:52:11 by vstockma         ###   ########.fr       */
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
		if (s[end] == '$' || ft_isspace(s[end]))
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
		else if (s[i] == '\0')
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

static void	ft_print_herdoc(char **hdoc, t_mini *mini)
{
	int	i;

	mini->hdoc_output = malloc(1024 * sizeof(char *));
	i = 0;
	while (hdoc[i])
	{
		mini->hdoc_output[i] = ft_replace_line(hdoc[i], mini);
		ft_putendl_fd(mini->hdoc_output[i], mini->input_fd);
		free(mini->hdoc_output[i]);
		i++;
	}
	free(mini->hdoc_output);
}

static void	ft_heredoc_loop(t_mini *mini, char *inp_line, char *delim)
{
	int		j;
	char	*new_delim;

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
			break ;
		}
		mini->heredoc[j] = ft_strdup(inp_line);
		j++;
		free(inp_line);
	}
	mini->heredoc[j] = NULL;
	free(inp_line);
}

int	ft_read_input_redirection(t_mini *mini, int i)
{
	char	*input_line;
	char	*delimiter;

	delimiter = ft_strdup(mini->args[i + 1]);
	input_line = NULL;
	mini->heredoc = malloc(sizeof(char *) * 1024);
	if (!mini->heredoc)
	{
		printf("Heredoc malloc failed\n");
		ft_free_malloc(mini);
	}
	ft_heredoc_loop(mini, input_line, delimiter);
	free(delimiter);
	if (i == 0)
		return (1);
	if (mini->here == mini->count_heredoc)
		ft_print_herdoc(mini->heredoc, mini);
	ft_free_2d_arr(mini->heredoc);
	return (0);
}
