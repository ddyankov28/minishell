/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handle_fds.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:54:49 by vstockma          #+#    #+#             */
/*   Updated: 2023/06/27 21:55:23 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_apply_input_redirections(t_mini *mini)
{
	if (ft_check_if_command(mini))
		return ;
	if (mini->input_fd != -1)
	{
		mini->stdin_copy = dup(STDIN_FILENO);
		dup2(mini->input_fd, STDIN_FILENO);
		close(mini->input_fd);
	}
}

void	ft_restore_and_close_fds(t_mini *mini)
{
	if (mini->stdin_copy != -1)
	{
		dup2(mini->stdin_copy, STDIN_FILENO);
		close(mini->stdin_copy);
	}
	if (mini->stdout_copy != -1)
	{
		dup2(mini->stdout_copy, STDOUT_FILENO);
		close(mini->stdout_copy);
	}
}

int	ft_redirect_right_check(t_mini *mini)
{
	if (ft_check_if_command(mini))
		return (1);
	if (mini->stdout_copy != -1)
	{
		dup2(mini->stdout_copy, STDOUT_FILENO);
		close(mini->stdout_copy);
	}
	return (0);
}
