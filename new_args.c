/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:07:05 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/31 12:58:05 by vstockma         ###   ########.fr       */
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
	ft_allocate_and_initiate(mini);
	if (ft_question(mini) == 0)
		return (0);
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
	if (mini->z == mini->xx)
	{
		if (mini->args[mini->xx][mini->j] == '\"')
		{
			ft_delete_quotes_for_str(mini, mini->xx);
			mini->sw_dollar = 2;
			ft_write_quotes(mini);
		}
		else if (mini->args[mini->xx][mini->j] == '\'')
		{
			ft_delete_quotes_for_str(mini, mini->xx);
			mini->sw_dollar = 1;
			ft_write_quotes(mini);
		}
		mini->z++;
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
		ft_skip_dollar(mini);
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
