/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_unset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:45:56 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/14 17:28:31 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_handle_export(t_mini *mini)
{
	char	*name;

	if (mini->args[1] != NULL)
	{
		name = ft_name(mini);
		if (mini->export_sw != 0 || ft_isdigit(mini->args[1][0]))
		{
			ft_printf("minishell: export: %s: not a valid identifier\n",
				mini->args[1]);
			mini->exit_value = 1;
			free(name);
			return ;
		}
		if (name != NULL && mini->value != NULL)
		{
			mini->env = ft_set_environment_variable(name, mini->value,
					mini->env);
			free(mini->value);
			free(name);
		}
	}
	else
		ft_show_environment(mini);
}

char	**ft_set_environment_variable(const char *name, char *value, char **env)
{
	int		count;
	char	**modified_env;

	count = 0;
	while (env[count] != NULL)
	{
		if (strncmp(env[count], name, ft_strlen(name)) == 0
			&& env[count][ft_strlen(name)] == '=')
		{
			free(env[count]);
			env[count] = ft_strdup(value);
			return (env);
		}
		count++;
	}
	modified_env = (char **)ft_calloc((count + 2), sizeof(char *));
	if (modified_env == NULL)
	{
		free(modified_env);
		return (NULL);
	}
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
