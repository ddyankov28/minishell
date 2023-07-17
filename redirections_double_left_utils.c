/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_double_left_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:35:19 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/17 14:09:03 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char*	ft_replace_line(char* s, t_mini *mini) 
{
    int start = 0;
    int end = 0;
    char* value = NULL;
    char* output = malloc(1024);
	int i = 0;
	int output_len = 0;
    
    while (s[i]) 
	{
        if (s[i] == '$') 
		{
            start = i + 1;
            end = i + 1;
            while (s[end])
			{
				if (s[end] == '$' || ft_isspace(s[end]))
					break ;
                end++;
				i++;
			}
            int var_name_len = end - start;
            char* var_name = ft_substr(s, start, var_name_len);
            value = ft_get_value_from_env(mini->env, var_name);
            if (value) 
			{
                ft_strncpy(output + output_len, value, ft_strlen(value));
                output_len += ft_strlen(value);
            	free(var_name);
            }
			else
				free(var_name);
        }
		else if (s[i] == '\0')
			break ;
		else 
		{
            output[output_len] = s[i];
            output_len++;
        }
		i++;
    }
    output[output_len] = '\0';
    return output;
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
	int	j;

	j = 0;
	while (1)
	{
		inp_line = readline("> ");
		if (!inp_line)
			break ;
		if (!ft_strncmp(inp_line, delim, ft_strlen(delim))
			&& (inp_line[ft_strlen(delim)] == '\n'
				|| inp_line[ft_strlen(delim)] == '\0'))
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

int	ft_read_input_redirection(t_mini *mini, char *delimiter, int i)
{
	char	*input_line;

	input_line = NULL;
	mini->heredoc = malloc(sizeof(char *) * 1024);
	if (!mini->heredoc)
	{
		printf("Heredoc malloc failed\n");
		ft_free_malloc(mini);
		return (1);
	}
	ft_heredoc_loop(mini, input_line, delimiter);
	if (i == 0)
		return (1);
	if (mini->here == mini->count_heredoc)
		ft_print_herdoc(mini->heredoc, mini);
	ft_free_2d_arr(mini->heredoc);
	return (0);
}
