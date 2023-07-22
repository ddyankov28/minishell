/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:59:13 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/22 12:07:31 by ddyankov         ###   ########.fr       */
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

int	ft_check_folder(t_mini *mini)
{
	char	**dirs;
	char	*path;
	int		i;

	path = ft_get_value_from_env(mini->env, "PATH");
	if (!path)
		return (1);
	dirs = ft_split(path, ':');
	i = 0;
	while (dirs[i])
	{
		if (!ft_strncmp(dirs[i], mini->args[0], ft_strlen(mini->args[0])))
		{
			ft_free_2d_arr(dirs);
			return (0);
		}
		i++;
	}
	ft_free_2d_arr(dirs);
	return (1);
}

void	ft_fork_error(void)
{
	perror("Fork failed");
	exit(1);
}
