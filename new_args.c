/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:07:05 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/27 16:20:18 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	ft_break(t_mini *mini)
{
	if (mini->args[mini->xx][mini->j] == ' '
		|| mini->args[mini->xx][mini->j] < 'A'
		|| (mini->args[mini->xx][mini->j] > 'Z'
			&& mini->args[mini->xx][mini->j] < 'a')
		|| mini->args[mini->xx][mini->j] > 'z')
		return (1);
	return (0);
}

static int	ft_if_dollar(t_mini *mini)
{
	mini->a = 0;
	mini->str_to_look = ft_calloc(1024, 1);
	mini->j++;
	mini->env_index = 0;
	while (mini->args[mini->xx][mini->j] != '$' && mini->args[mini->xx][mini->j]
		&& mini->args[mini->xx][mini->j] != ' ')
	{
		mini->str_to_look[mini->a++] = mini->args[mini->xx][mini->j++];
		if (ft_break(mini) == 1)
			break ;
	}
	mini->envvv = ft_get_value_from_env(mini->env, mini->str_to_look);
	free(mini->str_to_look);
	if (!mini->envvv)
		return (1);
	while (mini->envvv[mini->env_index] && mini->envvv[mini->env_index] != ' ')
		mini->new_str[mini->in++] = mini->envvv[mini->env_index++];
	if (mini->envvv[mini->env_index] == ' ')
	{
		mini->swit = 1;
		mini->env_index++;
		return (2);
	}
	mini->sw_dollar = 0;
	return (0);
}

static int	ft_if_quotes(t_mini *mini)
{
	static int	count;

	if (count == mini->xx)
	{
		if (mini->args[mini->xx][mini->j] == '\"')
		{
			ft_delete_quotes_for_str(mini, mini->xx);
			mini->sw_dollar = 2;
		}
		else if (mini->args[mini->xx][mini->j] == '\'')
		{
			ft_delete_quotes_for_str(mini, mini->xx);
			mini->sw_dollar = 1;
		}
		count++;
	}
	return (0);
}

static int	ft_init_and_break(t_mini *mini, int y)
{
	if (y == 1)
	{
		mini->sw_dollar = 0;
		mini->new_str = malloc(1024);
		if (!mini->new_str)
		{
			free(mini->new_str);
			ft_free_malloc(mini);
		}
		mini->in = 0;
		mini->j = 0;
	}
	else
	{
		if (mini->space_flag[mini->xx] == 1
			&& mini->args[mini->xx][mini->j] == '\0')
			return (1);
		if (mini->args[mini->xx][mini->j] == '\0')
		{
			mini->j = 0;
			mini->xx++;
		}
	}
	return (0);
}

char	*ft_get_new_str(t_mini *mini)
{
	ft_init_and_break(mini, 1);
	while (mini->args[mini->xx])
	{
		ft_if_quotes(mini);
		if (ft_x(mini) == 1)
		{
			mini->abc = ft_if_dollar(mini);
			if (mini->abc == 1)
				continue ;
			else if (mini->abc == 2)
				break ;
		}
		else if (mini->swit == 1)
		{
			if (ft_swit(mini) == 1)
				break ;
		}
		else if (mini->args[mini->xx][mini->j] != '\0')
			mini->new_str[mini->in++] = mini->args[mini->xx][mini->j++];
		if (ft_init_and_break(mini, 0) == 1)
			break ;
	}
	mini->new_str[mini->in] = '\0';
	return (mini->new_str);
}
