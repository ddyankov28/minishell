/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:38:55 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/31 14:17:23 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_expand_str(t_mini *mini, int i)
{
	int		j;
	char	*env_var;
	char	*str_to_look;
	int		index;

	index = 0;
	j = 0;
	ft_delete_quotes_for_str(mini, i);
	if (mini->args[i][j] == '$')
	{
		str_to_look = ft_calloc(1024, 1);
		j++;
		while (ft_isalpha(mini->args[i][j]) && mini->args[i][j])
			str_to_look[index++] = mini->args[i][j++];
		env_var = ft_get_value_from_env(mini->env, str_to_look);
		free(str_to_look);
		if (!env_var)
			return (printf("minishell: %s: ambiguous redirect\n",
					mini->args[i]), 1);
		free(mini->args[i]);
		mini->args[i] = ft_strdup(env_var);
	}
	mini->is_redirection = 1;
	return (0);
}

static int	ft_check_new_str(t_mini *mini, char *new_str)
{
	if (ft_strcmp(new_str, "\0") == 0)
	{
		if (mini->xx != mini->index)
			mini->xx++;
		free(new_str);
		return (1);
	}
	return (0);
}

static void	ft_i_cant_anymore(t_mini *mini, int i)
{
	if (i != mini->index + 1)
		free(mini->args[i]);
	mini->args[i] = NULL;
	if (mini->index <= i)
		mini->index = i;
}

static int	ft_expand_expandation(t_mini *mini, char *new_str, int i)
{
	while (mini->xx < mini->index)
	{
		new_str = ft_get_new_str(mini);
		if (ft_check_new_str(mini, new_str) == 1)
			continue ;
		free(mini->args[i]);
		mini->args[i] = ft_strdup(new_str);
		free(new_str);
		if (mini->swit == 1)
		{
			i++;
			continue ;
		}
		if (mini->args[mini->xx] == NULL)
		{
			i++;
			break ;
		}
		mini->xx++;
		i++;
		mini->swit = 0;
	}
	ft_i_cant_anymore(mini, i);
	return (0);
}

int	ft_expand(t_mini *mini)
{
	char	*new_str;
	int		i;

	i = 0;
	mini->swit = 0;
	new_str = NULL;
	if (ft_is_builtin(mini, mini->args[0]))
		return (1);
	ft_expand_expandation(mini, new_str, i);
	return (0);
}
