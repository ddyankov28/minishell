/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:46:43 by ddyankov          #+#    #+#             */
/*   Updated: 2023/07/31 16:14:03 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_echo_env(t_mini *mini, char *args)
{
	char	*env_value;

	env_value = ft_get_value_from_env(mini->env, args);
	if (env_value != NULL)
		write(1, env_value, ft_strlen(env_value));
}

int	ft_split_double(t_mini *mini, char *args, int i)
{
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(args) + 1));
	if (!str)
	{
		free(str);
		ft_free_malloc(mini);
	}
	i++;
	if (args[i] == '?')
	{
		ft_printf("%d", mini->exit_value);
		mini->exit_value = 0;
		i++;
	}
	else
		i = ft_envval_doublequote(mini, args, str, i);
	return (i);
}

int	ft_envval_doublequote(t_mini *mini, char *args, char *str, int i)
{
	int	counter;
	int	j;

	j = 0;
	counter = 0;
	if (args[i] >= '0' && args[i] <= '9')
		counter++;
	while (args[i] && args[i] != '$' && args[i] != '"' && args[i] != ' ')
	{
		if (args[i] == '\'')
			break ;
		str[j] = args[i];
		i++;
		j++;
		if (args[i] >= '0' && args[i] <= '9' && counter == 1)
		{
			if (args[i + 1] == '\0' || args[i + 1] == '"')
				ft_putchar_fd(args[i], mini->fd);
			break ;
		}
	}
	str[j] = '\0';
	ft_echo_env(mini, str);
	free(str);
	return (i);
}

int	ft_split_unclosed(t_mini *mini, char *args, int i)
{
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(args) + 1));
	if (!str)
	{
		free(str);
		ft_free_malloc(mini);
	}
	i++;
	if (args[i] == '?')
	{
		ft_printf("%d", mini->exit_value);
		mini->exit_value = 0;
		i++;
	}
	else
		i = ft_envval_unclosed(mini, args, str, i);
	free(str);
	return (i);
}

int	ft_envval_unclosed(t_mini *mini, char *args, char *str, int i)
{
	int	j;
	int	counter;

	counter = 0;
	j = 0;
	if (args[i] >= '0' && args[i] <= '9')
		counter++;
	while (args[i] && args[i] != '$')
	{
		str[j] = args[i];
		i++;
		j++;
		if (args[i] >= '0' && args[i] <= '9' && counter == 1)
		{
			if (args[i + 1] == '\0')
				ft_putchar_fd(args[i], mini->fd);
			break ;
		}
		if (args[i] <= 47 || (args[i] >= 58 && args[i] <= 64) || (args[i] >= 91
				&& args[i] <= 94) || args[i] == 96 || args[i] >= 123)
			break ;
	}
	str[j] = '\0';
	ft_echo_env(mini, str);
	return (i);
}
