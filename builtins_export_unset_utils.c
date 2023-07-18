/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_unset_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:39:47 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/18 12:37:27 by ddyankov         ###   ########.fr       */
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
		name[i] = mini->args[1][i];
		if ((mini->args[1][i] >= 33 && mini->args[1][i] <= 47)
			|| (mini->args[1][i] >= 58 && mini->args[1][i] <= 60)
			|| (mini->args[1][i] >= 62 && mini->args[1][i] <= 64)
			|| (mini->args[1][i] >= 91 && mini->args[1][i] <= 96)
			|| (mini->args[1][i] >= 123 && mini->args[1][i] <= 126))
			mini->export_sw++;
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
	ft_value(mini);
	return (name);
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
		if (mini->args[i + 1] == NULL)
			return (0);
		ft_delete_quotes_for_str(mini, i + 1);
		if (mini->space_flag[i] == 1)
			return (0);
		tmp = ft_strjoin(mini->value, mini->args[i + 1]);
		free(mini->value);
		mini->value = ft_strdup(tmp);
		free(tmp);
		i++;
	}
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
