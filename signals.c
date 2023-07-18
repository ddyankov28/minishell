/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:38:04 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/18 12:36:42 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

void	ft_ctrl_d(t_mini *mini)
{
	if (!mini->input)
	{
		printf("exit\n");
		free(mini->input);
		ft_free_2d_arr(mini->env);
		exit(0);
	}
}

void	ft_write_space(t_mini *mini, int index)
{
	if (mini->space_or_not == 0)
	{
		if (mini->space_flag[index] == 1)
			ft_putchar_fd(' ', mini->fd);
	}
}

int	ft_check_n(t_mini *mini, int j)
{
	char	pair_quote;
	int		i;

	pair_quote = '\0';
	i = 0;
	if (!mini->args[j])
		return (1);
	if (mini->args[j][i] == '"' || mini->args[j][i] == '\'')
	{
		pair_quote = mini->args[j][i];
		if (ft_look_for_quote(mini, mini->args[j], i) == 0)
			return (1);
		i++;
	}
	if (mini->args[j][i++] != '-')
		return (1);
	if (mini->args[j][i] == '\0')
		return (1);
	while (mini->args[j][i] && mini->args[j][i] != pair_quote)
	{
		if (mini->args[j][i] != 'n')
			return (1);
		i++;
	}
	return (0);
}
