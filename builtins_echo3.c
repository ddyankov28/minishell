/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:59:13 by vstockma          #+#    #+#             */
/*   Updated: 2023/06/27 16:43:07 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_check_for_end(char *str, int i)
{
	if (str[i + 1] == '\0' || str[i + 1] == '"')
	{
		if (str[i] == '\'')
		{
			ft_putchar_fd('\'', 1);
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
					ft_putchar_fd('$', 1);
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
			ft_putchar_fd(args[i], 1);
			i++;
		}
	}
	return (0);
}
