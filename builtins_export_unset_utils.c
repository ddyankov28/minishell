/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_unset_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:39:47 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/18 16:50:18 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	*ft_name_extension(t_mini *mini, char *name)
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
			mini->plus++;
		name[i] = mini->args[1][i];
		ft_check_chars(mini, i);
		if (mini->args[1][i] == '=')
		{
			mini->count++;
			break ;
		}
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*ft_name(t_mini *mini)
{
	char	*name;

	if (mini->args[1] == NULL)
		return (NULL);
	name = malloc(sizeof(char) * ft_strlen(mini->args[1]) + 1);
	if (!name)
	{
		free(name);
		ft_free_malloc(mini);
		return (NULL);
	}
	name = ft_name_extension(mini, name);
	if (mini->count == 0)
	{
		free(name);
		return (NULL);
	}
	if (mini->plus > 1)
		mini->export_sw++;
	ft_value(mini, name);
	return (name);
}

int	ft_value(t_mini *mini, char *name)
{
	char	*tmp;
	int		i;

	i = 1;
	ft_delete_quotes_for_str(mini, 1);
	mini->value = ft_strdup(mini->args[1]);
	while (mini->args[i])
	{
		if (ft_value_return(mini, i, name) == 0)
			return (0);
		ft_delete_quotes_for_str(mini, i + 1);
		if (mini->space_flag[i] == 1)
		{
			ft_final_value(mini, mini->value, name);
			return (0);
		}
		tmp = ft_strjoin(mini->value, mini->args[i + 1]);
		free(mini->value);
		mini->value = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	ft_final_value(mini, mini->value, name);
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
