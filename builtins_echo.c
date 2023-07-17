/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:46:30 by ddyankov          #+#    #+#             */
/*   Updated: 2023/07/17 17:19:14 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_check_n(t_mini *mini, int j)
{
	int	i;

	i = 0;
	if (mini->args[j][i] == '"')
		i++;
	if (mini->args[j][i] != '-')
		return (1);
	i++;
	if (mini->args[j][i] == '\0')
		return (1);
	while (mini->args[j][i] && mini->args[j][i] != '"')
	{
		if (mini->args[j][i] != 'n')
			return (1);
		i++;
	}
	if (mini->space_flag[j] == 0)
		return (1);
	return (0);
}

void	ft_handle_echo(t_mini *mini)
{
	int	i;

	i = 1;
	if (!mini->args[1])
	{
		ft_putchar_fd('\n', mini->fd);
		return ;
	}
	if (ft_check_n(mini, i) == 0)
	{
		while (ft_check_n(mini, i) == 0)
			i++;
		if (!mini->args[i])
			return ;
		ft_echo(mini, mini->args, i);
	}
	else
	{
		ft_echo(mini, mini->args, 1);
		ft_putchar_fd('\n', mini->fd);
	}
}

void	ft_echo(t_mini *mini, char **args, int i)
{
	while (args[i])
	{
		if (args[i][0] == '\"' && ft_look_for_quote(mini, args[i], 0))
			ft_echo_double(mini, args[i], i);
		else if (args[i][0] == '\'' && ft_look_for_quote(mini, args[i], 0))
			ft_echo_single(mini, args[i], i);
		else
			ft_echo_unclosed(mini, args[i], i);
		i++;
	}
}

void	ft_echo_double(t_mini *mini, char *args, int index)
{
	int	i;

	i = 1;
	while (args[i] != '"')
	{
		if (args[i] == '$')
		{
			while (args[i] == '$')
			{
				if (args[i + 1] == '\0' || args[i + 1] == '"'
					|| args[i + 1] == ' ')
				{
					ft_putchar_fd('$', mini->fd);
					i++;
					break ;
				}
				i = ft_split_double(mini, args, i);
			}
			if (ft_check_for_end(mini, args, i) == 1)
				break ;
		}
		ft_putchar_fd(args[i], mini->fd);
		i++;
	}
	ft_write_space(mini, index);
}

void	ft_echo_single(t_mini *mini, char *args, int index)
{
	int	i;

	i = 1;
	while (args[i] != '\'')
	{
		ft_putchar_fd(args[i], mini->fd);
		i++;
	}
	ft_write_space(mini, index);
}

void	ft_echo_unclosed(t_mini *mini, char *args, int index)
{
	int	i;

	i = 0;
	if (ft_strcmp(args, "$") == 0 && mini->args[index + 1] != NULL
		&& mini->space_flag[index] == 0)
		return ;
	ft_echo_unclosed_loop(mini, args, i);
	ft_write_space(mini, index);
}
