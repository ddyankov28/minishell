/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_unset_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:39:47 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/31 12:28:48 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_name_extension(t_mini *mini)
{
	int	i;

	mini->count = 0;
	i = 0;
	while (mini->args[1][i])
	{
		if (mini->args[1][i] == '+' && mini->args[1][i + 1] == '=')
		{
			mini->plus++;
			i++;
		}
		else if (mini->args[1][i] == '+')
			mini->export_sw++;
		mini->name[i] = mini->args[1][i];
		ft_check_chars(mini, i);
		if (mini->args[1][i] == '=')
		{
			mini->count++;
			break ;
		}
		i++;
	}
	mini->name[i] = '\0';
}

int	ft_name(t_mini *mini)
{
	if (mini->args[1] == NULL)
		return (1);
	mini->name = ft_calloc(200, sizeof(char));
	if (!mini->name)
	{
		free(mini->name);
		ft_free_malloc(mini);
		return (1);
	}
	ft_name_extension(mini);
	if (mini->count == 0)
	{
		free(mini->name);
		mini->name = NULL;
		return (1);
	}
	if (mini->plus > 1)
		mini->export_sw++;
	if (mini->export_sw != 0)
		return (1);
	ft_value(mini);
	return (0);
}

int	ft_extendination(t_mini *mini, int i)
{
	if (ft_valid_or_not(mini, i + 1) == 1)
		return (1);
	ft_delete_quotes_for_str(mini, i + 1);
	return (0);
}

int	ft_value(t_mini *mini)
{
	char	*tmp;
	int		i;

	i = 1;
	ft_delete_quotes_for_str(mini, 1);
	mini->value = ft_strdup(mini->args[1]);
	while (mini->args[i])
	{
		if (ft_value_return(mini, i) == 0)
			return (0);
		if (ft_extendination(mini, i) == 1)
			return (0);
		if (mini->space_flag[i] == 1)
		{
			ft_final_value(mini, mini->value);
			return (0);
		}
		tmp = ft_strjoin(mini->value, mini->args[i + 1]);
		free(mini->value);
		mini->value = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	ft_final_value(mini, mini->value);
	return (1);
}

int	ft_env(char **env, char **new_env)
{
	int	count;

	count = 0;
	while (env[count])
	{
		new_env[count] = ft_strdup(env[count]);
		count++;
	}
	new_env[count] = NULL;
	return (0);
}
