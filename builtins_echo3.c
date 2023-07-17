/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:59:13 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/17 17:19:24 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_check_for_end(t_mini *mini, char *str, int i)
{
	if (str[i + 1] == '\0' || str[i + 1] == '"')
	{
		if (str[i] == '\'')
		{
			ft_putchar_fd('\'', mini->fd);
		}
		return (1);
	}
	return (0);
}

int	ft_echo_unclosed_loop(t_mini *mini, char *args, int i)
{
	while (args[i])
	{
		if (args[i] == '$')
		{
			while (args[i] == '$')
			{
				if (args[i + 1] == '\0')
				{
					ft_putchar_fd('$', mini->fd);
					i++;
					break ;
				}
				i = ft_split_unclosed(mini, args, i);
			}
			if (args[i] == '\0')
				break ;
		}
		else
		{
			ft_putchar_fd(args[i], mini->fd);
			i++;
		}
	}
	return (0);
}
