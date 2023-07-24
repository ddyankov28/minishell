/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifying_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:56:04 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/24 11:51:20 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_strcmp_with_quotes(t_mini *mini, char *str, char *builtin)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[i] == '\'' || str[i] == '"')
	{
		if (ft_look_for_quote(mini, str, i) == 0)
			return (1);
		i++;
	}
	if (str[i] == '\'' || str[i] == '"')
		return (1);
	i = ft_strcmp_with_quotes_extension(mini, str, builtin, i);
	if (i != 0)
		return (1);
	return (0);
}

int	ft_strcmp_with_quotes_extension(t_mini *mini, char *str, char *builtin,
		int i)
{
	int	j;

	j = 0;
	while ((str[i] != '\0' || builtin[j] != '\0') && j < ft_strlen(builtin))
	{
		if (str[i] > builtin[j])
			return (-1);
		if (str[i] < builtin[j])
			return (-1);
		i++;
		j++;
	}
	if (str[i] == '\'' || str[i] == '"')
	{
		if (mini->flag_for_pair == 0)
			return (1);
		else if (str[++i] != '\0')
			return (1);
		else
			return (0);
	}
	else if (str[i] != '\0')
		return (1);
	return (0);
}

void	ft_write_without_quotes(t_mini *mini, char *str)
{
	int		i;
	char	pair;

	i = 0;
	pair = '\'';
	if (str[i] == '\'' || str[i] == '"')
	{
		pair = str[i];
		ft_look_for_quote(mini, str, 0);
		if (mini->flag_for_pair == 1)
			i++;
	}
	while (str[i])
	{
		if (str[i] == pair && mini->flag_for_pair == 1)
			break ;
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_delete_quotes(t_mini *mini)
{
	int	i;
	int	j;

	i = 0;
	while (mini->args[i])
	{
		if (mini->args[i][0] == '\'' || mini->args[i][0] == '"')
		{
			if (ft_look_for_quote(mini, mini->args[i], 0) == 1)
			{
				j = 0;
				while (mini->args[i][j])
				{
					mini->args[i][j] = mini->args[i][j + 1];
					j++;
				}
				mini->args[i][j - 2] = '\0';
			}
		}
		i++;
	}
	return (0);
}

int	ft_delete_quotes_for_str(t_mini *mini, int i)
{
	int	j;

	if (mini->args[i][0] == '\'' || mini->args[i][0] == '"')
	{
		if (ft_look_for_quote(mini, mini->args[i], 0) == 1)
		{
			j = 0;
			while (mini->args[i][j])
			{
				mini->args[i][j] = mini->args[i][j + 1];
				j++;
			}
			mini->args[i][j - 2] = '\0';
		}
	}
	return (0);
}
