/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_unset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:45:56 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/25 09:46:01 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_handle_export(t_mini *mini)
{
	int	name;

	if (mini->args[1] != NULL)
	{
		name = ft_name(mini);
		if (mini->export_sw != 0 || ft_isdigit(mini->args[1][0])
			|| mini->args[1][0] == '=')
		{
			ft_not_valid(mini);
			return ;
		}
		if (name != 1 && mini->value != NULL)
		{
			mini->env = ft_set_env_var(mini->name, mini->value,
					mini->env, mini);
			free(mini->value);
			free(mini->name);
		}
	}
	else
		ft_show_environment(mini);
}

static void	ft_check_malloc(char **modified_env, t_mini *mini)
{
	if (!modified_env)
	{
		free(modified_env);
		ft_free_malloc(mini);
	}
}

char	**ft_set_env_var(char *name, char *value, char **env, t_mini *mini)
{
	int		count;
	char	**modified_env;

	count = 0;
	while (env[count] != NULL)
	{
		if (ft_strncmp(env[count], name, ft_strlen(name)) == 0
			&& env[count][ft_strlen(name)] == '=')
		{
			free(env[count]);
			env[count] = ft_strdup(value);
			return (env);
		}
		count++;
	}
	modified_env = (char **)ft_calloc((count + 2), sizeof(char *));
	ft_check_malloc(modified_env, mini);
	ft_env(env, modified_env);
	ft_free_2d_arr(env);
	modified_env[count] = ft_strdup(value);
	modified_env[count + 1] = NULL;
	return (modified_env);
}

char	**ft_unset_environment_variable(t_mini *mini)
{
	int		count;
	char	**modified_env;

	if (mini->args[1] == NULL)
		return (mini->env);
	ft_delete_quotes_for_str(mini, 1);
	count = 0;
	while (mini->env[count] != NULL)
		count++;
	modified_env = ft_modified_env(mini, count);
	ft_free_2d_arr(mini->env);
	return (modified_env);
}

char	**ft_modified_env(t_mini *mini, int count)
{
	int		index;
	int		i;
	char	**modified_env;

	i = 0;
	index = 0;
	modified_env = malloc((count + 1) * sizeof(char *));
	if (!modified_env)
	{
		free(modified_env);
		ft_free_malloc(mini);
	}
	while (mini->env[i] != NULL)
	{
		if (ft_strncmp(mini->args[1], mini->env[i],
				ft_strlen(mini->args[1])) != 0
			|| mini->env[i][ft_strlen(mini->args[1])] != '=')
		{
			modified_env[index] = ft_strdup(mini->env[i]);
			index++;
		}
		i++;
	}
	modified_env[index] = NULL;
	return (modified_env);
}
