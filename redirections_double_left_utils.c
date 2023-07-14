/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_double_left_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:35:19 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/14 18:39:54 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_print_herdoc(char **heredoc, t_mini *mini)
{
	int	i;
	char *env_value = NULL;

	i = 0;
	while (heredoc[i])
	{
		if (heredoc[i][0] == '$')
		{
			env_value = ft_get_value_from_env(mini->env, ft_substr(heredoc[i], 1 , ft_strlen(heredoc[i])));
			ft_putstr_fd(env_value, 1);
		}
		else
			ft_putstr_fd(heredoc[i], 1);	
		ft_putstr_fd("\n", 1);
		i++;
	}
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
